
import {kStringMaxLength} from 'buffer';
import fs from 'fs';
import path from 'path';

const dir       = path.normalize(path.join(__dirname, '../../../../cocos/bindings/auto'));
const jsonFiles = fs.readdirSync(dir).filter(x => x.endsWith('.json')).map(x => path.join(dir, x));


let outFile = fs.openSync(path.join(__dirname, 'jsb_auto.d.ts'), 'w');

let all_classes: NativeClass[] = [];
for (let f of jsonFiles) {
    console.log(`require ${f}`);
    const content = fs.readFileSync(f).toString();
    if (content.length > 0) {
        all_classes = all_classes.concat(JSON.parse(content));
    }
}

let nameToClass: {[key: string]: NativeClass}     = {};
let nsToClass: {[key: string]: NativeClass[]}     = {};
let fullNameToClass: {[key: string]: NativeClass} = {};


namespace utils {

    function fullClassNameToTS(name: string) {
        let m = fullNameToClass[name];
        if (m) {
            return `${m.script_ns}`;
        }
        return 'unknown';
    }

    function convert_vector(r: RegExpMatchArray): string {
        return `: ${fullClassNameToTS(r[1])}[]`;
    }
    function convert_shared_ptr(r: RegExpMatchArray): string {
        return `: ${fullClassNameToTS(r[1])}`;
    }

    function convert_optional(r: RegExpMatchArray): string {
        return `?: ${fullClassNameToTS(r[1])}`;
    }

    function convert_typed_array(r: RegExpMatchArray): string {
        let c = r[1];
        if(/unsigned char/.test(c)) {
            return ": Uint8Array";
        }
        if(/char/.test(c)) {
            return ": Int8Array";
        }
        return ": TypedArray";
    }

    function convert_to_any(r: RegExpMatchArray): string {
        return `: any /* ${r[0]} */`;
    }

    function convert_to_unknown(r: RegExpMatchArray): string {
        return `: unknown /* ${r[0]} */`;
    }


    let convert_map: [RegExp, string|{(r: RegExpMatchArray): string}][] = [
        [/char*/, 'string'],
        [/\w+ int/, 'number'],
        [/\w+ char/, 'number'],
        [/float|double/, 'number'],
        [/int|long/, 'number'],
        [/bool/, 'boolean'],
        [/nowhere/, convert_to_unknown],
        [/std::any/,'any'],
        [/std.*string/, 'string'],
        [/cc.*ArrayBuffer/, 'ArrayBuffer'],
        [/std::vector<([^>\s]+).*>/, convert_vector],
        [/std::shared_ptr<([^>\s]+).*>/, convert_shared_ptr],
        [/std::optional<([^>\s]+).*>/, convert_shared_ptr],
        [/std::function<([^>\s]+).*>/, convert_optional],
        [/cc::TypedArrayTemp<([^>\s]+).*>/, convert_to_unknown],
        [/cc.Mesh::IStruct/, "unknown /* cc.Mesh::IStruct */"], //TODO(PatriceJiang): export this
        [/cc.Mesh::ICreateInfo/, "unknown /* cc.Mesh::ICreateInfo */"], //TODO(PatriceJiang): export this
    ];

    export function fix_type_name(t: NativeType) {
        for (let x of convert_map) {
            const r = t.script_ns.match(x[0]);
            if (r) {
                return typeof x[1] === 'function' ? x[1](r) : `: ${x[1]}`;
            }
        }

        let kls = nameToClass[t.script_ns];
        // treat enum as number
        if (!kls && t.is_enum) {
            return ': number';
        }
        if(!kls && t.script_ns.startsWith("sp.")){
            return `: unknown /*${t.script_ns}*/`;
        }

        return `: ${t.script_ns}`;
    }

}

const UF = utils.fix_type_name;

function processMethod(m: NativeFunction|NativeOverloadedFunction):string[] {
    let overloaded = m as NativeOverloadedFunction;
    let method = m as NativeFunction;
    let name = m.name;
    if(overloaded.implementations){
        let ret:string[] = [];
        for(let x of overloaded.implementations) {
            ret = ret.concat(processMethod(x));
        }
        return ret;
    } else {
        let args = method.arguments.map((x, i) => `arg${i}${UF(x)}`).join(", ");
        if(method.is_constructor) {
            return [`constructor(${args});`];
        }
        const prefix = args.indexOf("??") > 0 ? "// " : "";
        return [`${prefix}${name}(${args})${UF(method.ret_type)};`]
    }
}


function processClass(klass: NativeClass): string {
    let buffer: string[] = [];
    buffer.push('\n');
    buffer.push(`// ts : ${klass.script_ns}\n// cpp: ${klass.namespaced_class_name}`);
    buffer.push(`export class ${klass.class_name} {`);


    if (klass.getter_setter.length > 0) {
        //export attributes
        {
            let attrBuffer: string[] = [];
            attrBuffer.push(`// attributes list`);
            for (let attr of klass.getter_setter) {
                attrBuffer.push(`declare ${attr.name}${UF(attr.type)}; //${attr.type.namespaced_class_name}`);
            }
            buffer.push(addIndent(attrBuffer.join('\n'), 4))
        }
    }

    if(Object.keys(klass.methods).length > 0) {
        // export methods
        {
            {
                let methodBuffer: string[] = [];
                methodBuffer.push(`// methods list`);
                for (let attr in klass.methods) {
                    const m = klass.methods[attr];
                    if(attr.startsWith("operator")) continue;
                    methodBuffer.push(`${processMethod(m).join('\n')}`);
                }
                buffer.push(addIndent(methodBuffer.join('\n'), 4))
            }
        }
    }


    buffer.push(`} // endof class ${klass.class_name}`);
    return buffer.join('\n');
}

function addIndent(content: string, spaces: number): string {
    let sp: string = '';
    while (spaces-- > 0) {
        sp += ' ';
    }
    return content.split('\n').map(x => {
                                  if (!/^\s+$/.test(x)) {
                                      return `${sp}${x}`;
                                  } else {
                                      return x;
                                  }
                              })
        .join('\n');
}

all_classes.reduce((prev, curr) => {
    let ns = curr.script_ns.split('.');
    if (ns.length > 1) {
        ns.pop();
        prev[ns[0]] = prev[ns[0]] ? prev[ns[0]].concat(curr) : [curr];
    } else {
        console.error(`Skip bad namespace '${curr.script_ns}' from class ${curr.namespaced_class_name}`);
    }
    return prev;
}, nsToClass);

// setup table
all_classes.forEach(kls => {
    nameToClass[kls.script_ns]                 = kls;
    fullNameToClass[kls.namespaced_class_name] = kls;
});


const topBuffer: string[] = [];

for (let ns in nsToClass) {
    let klist = nsToClass[ns];
    topBuffer.push(`declare namespace ${ns} {`);
    topBuffer.push(addIndent(klist.map(processClass).join('\n'), 4));
    topBuffer.push(`} // endof namespace ${ns}\n`);
}



fs.writeFileSync(outFile, topBuffer.join('\n'));

fs.writeFileSync(outFile, `\n\n\n/////// ${all_classes.length} classes process!`);

fs.closeSync(outFile);

console.log(` -> ${all_classes.length}`);
