
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
            return m.script_ns;
        }
        return 'never';
    }

    function convert_vector(r: RegExpMatchArray): string {
        return `${fullClassNameToTS(r[1])}[]`;
    }

    let convert_map: [RegExp, string|{(r: RegExpMatchArray): string}][] = [
        [/\w+ int/, 'number'],
        [/float/, 'number'],
        [/int/, 'number'],
        [/std.*string/, 'string'],
        [/std::vector<([^>\s]+).*>/, convert_vector],
    ];

    export function fix_type_name(t: NativeType) {
        for (let x of convert_map) {
            const r = t.script_ns.match(x[0]);
            if (r) {
                return typeof x[1] === 'function' ? x[1](r) : x[1];
            }
        }

        let kls = nameToClass[t.script_ns];
        // treat enum as number
        if (!kls && t.is_enum) {
            return 'number';
        }

        return t.script_ns;
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
                attrBuffer.push(`${attr.name}: ${utils.fix_type_name(attr.type)}; //${attr.type.namespaced_class_name}`);
            }
            buffer.push(addIndent(attrBuffer.join('\n'), 4))
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
