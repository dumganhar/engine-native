
import {kStringMaxLength} from 'buffer';
import fs, {linkSync} from 'fs';
import path from 'path';

const dir       = path.normalize(path.join(__dirname, '../../../../cocos/bindings/auto'));
const jsonFiles = fs.readdirSync(dir).filter(x => x.endsWith('.json')).map(x => path.join(dir, x));
const outFilePath = path.join(__dirname, 'jsb_auto.d.ts');
const copyTo  = path.normalize(path.join(__dirname, '../../../../../engine/@types/jsb.auto.d.ts'));
const copyFiles:string[] = [path.join(__dirname, "../decl/predefine.d.ts"), outFilePath];

const outFile = fs.openSync(outFilePath, 'w');
const exportNamespaces = ['gfx', 'cc', 'nr', 'ns'];

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

    let additional_type_mape: any = {
        "cc::Vec3": "cc.Vec3",
    }

    export function fullClassNameToTS(name: string) {
        let m = fullNameToClass[name];
        if (m) {
            return `${m.script_ns}`;
        }
        let s = additional_type_mape[name];
        if(s) return s;
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
        if (/unsigned char/.test(c)) {
            return ': Uint8Array';
        }
        if (/char/.test(c)) {
            return ': Int8Array';
        }
        return ': TypedArray';
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
        [/std::any/, 'any'],
        [/std.*string/, 'string'],
        [/cc.*ArrayBuffer/, 'ArrayBuffer'],
        [/std::vector<([^>\s,]+).*>/, convert_vector],
        [/std::array<([^>\s,]+).*>/, convert_vector],
        [/std::shared_ptr<([^>\s,]+).*>/, convert_shared_ptr],
        [/std::optional<([^>\s,]+).*>/, convert_shared_ptr],
        [/std::function<([^>\s]+).*>/, convert_optional],
        [/cc::TypedArrayTemp<([^>\s]+).*>/, convert_to_unknown],
        [/cc.Mesh::IStruct/, 'unknown /* cc.Mesh::IStruct */'],         //TODO(PatriceJiang): export this
        [/cc.Mesh::ICreateInfo/, 'unknown /* cc.Mesh::ICreateInfo */'], //TODO(PatriceJiang): export this
        [/cc.Device::MotionValue/,'unknown /* cc.Device::MotionValue */'],//TODO(PatriceJiang): export this
    ];

    export function fix_type_name(t: {script_ns: string, is_enum: boolean}) {
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
        if (!kls && t.script_ns.startsWith('sp.')) {
            return `: unknown /*${t.script_ns}*/`;
        }

        return `: ${t.script_ns}`;
    }


    export function fix_type_name_clean(t: {script_ns: string, is_enum: boolean}) {
        let ret = fix_type_name(t);
        if (ret.startsWith('?: ')) {
            return ret.substr(3);
        }
        if (ret.startsWith(': ')) {
            return ret.substr(2);
        }
        return ret;
    }

    export function addIndent(content: string, spaces: number): string {
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

    export function align(alignment: number) {
        return (3 - (alignment + 3) % 4) + alignment;
    }

    export function alignText(text: string, alignment: number) {
        while (text.length < alignment) {
            text += ' ';
        }
        return text;
    }

    interface RecursiveArray<T> {
        [key: number]: T|RecursiveArray<T>;
        length: number
    }

    function flatMap<T>(data: RecursiveArray<T>, cb: (v: T) => T) {
        let ret: T[] = [];
        flatMapImpl(data, (v: T) => {
            ret.push(cb(v));
        });
        return ret;
    }

    function flatMapImpl<T>(data: RecursiveArray<T>, cb: (v: T) => void) {
        for (let i = 0; i < data.length; i++) {
            if (data[i] instanceof Array) {
                flatMapImpl(data[i] as RecursiveArray<T>, cb);
            } else {
                cb(data[i] as T);
            }
        }
    }

    export function formatComment(comment: string): string[] {
        return flatMap<string>(comment.split(/\<br\/?\>/).map(x => x.split('\n')), x => {
                   if (x.startsWith('*--')) {
                       return '   ' + x.substr(3);
                   }
                   if (x.startsWith('*')) {
                       return ' ' + x.substr(1);
                   }
                   if (x.startsWith('--')) {
                       return '  ' + x.substr(2);
                   }
                   return x;
               }).map(x => x.trim());//.filter(x=> x.length > 0);
    }

}

const UF  = utils.fix_type_name;
const UFC = utils.fix_type_name_clean;

function processMethod(m: NativeFunction|NativeOverloadedFunction): string[] {
    let overloaded      = m as NativeOverloadedFunction;
    let method          = m as NativeFunction;
    let            name = m.name;
    if (overloaded.implementations) {
        let ret: string[] = [];
        for (let x of overloaded.implementations) {
            ret = ret.concat(processMethod(x));
        }
        return ret;
    } else {
        let tips = method.argumentTips || [];
        let args = method.arguments.map((x, i) => `${tips[i] || ('arg' + i)}${UF(x)}`).join(', ');
        if (method.is_constructor) {
            //return [`new (${args}): ${method.current_class_name};`];
            return [`constructor(${args});`];
        }
        const prefix  = args.indexOf('??') > 0 ? '// ' : '';
        const comment = method.comment.length > 0 ? `/**\n${utils.formatComment(method.comment).map(x => ' * ' + x).join('\n')}\n */\n` : '';
        const static_prefix = method.static ? 'static ':'';
        return [`${comment}${prefix}${static_prefix}${name}(${args})${UF(method.ret_type)};`]
    }
}


function processClass(klass: NativeClass): string {
    let buffer: string[] = [];


    const extends_field = klass.parents.length == 0 ? '' :
                                                      `extends ${klass.parents.map(x => UFC({script_ns: utils.fullClassNameToTS(x), is_enum: false}))} `;

    buffer.push('\n');
    buffer.push(`// ts : ${klass.script_ns}\n// cpp: ${klass.namespaced_class_name}`);
    buffer.push(`export class ${klass.class_name} ${extends_field}{`);


    // if(klass.namespaced_class_name.indexOf("DrawInfo") >=0 ){
        // console.log(`attributes ${klass.getter_setter.map(x=>x.name)}`);
    // }

    if (klass.getter_setter.length > 0) {
        //export attributes
        {
            let attrBuffer: string[] = [];
            attrBuffer.push(`// attributes list`);
            let maxLeft                           = 0;
            let maxMiddle                         = 0;
            let lines: [string, string, string][] = [];
            for (let attr of klass.getter_setter) {
                let p: [string, string, string] = [`${attr.name}`, `${UF(attr.type)};`, `// ${attr.type.namespaced_class_name}`];
                maxLeft = Math.max(maxLeft, p[0].length);
                maxMiddle                       = Math.max(maxMiddle, p[1].length);
                lines.push(p);
            }
            let left   = utils.align(maxLeft);
            let middle = utils.align(maxMiddle);
            for (let l of lines) {
                attrBuffer.push([utils.alignText(l[0], left), utils.alignText(l[1], middle), l[2]].join(''));
            }

            buffer.push(utils.addIndent(attrBuffer.join('\n'), 4))
        }
    }

    if (klass.public_fields.length > 0) {
        //export attributes
        {
            let attrBuffer: string[] = [];
            attrBuffer.push(`// public_fields list`);
            let maxLeft                           = 0;
            let maxMiddle                         = 0;
            let lines: [string, string, string][] = [];
            for (let attr of klass.public_fields) {
                let p: [string, string, string] = [`${attr.name}`, `${UF(attr.type)};`, `// ${attr.type.namespaced_class_name}`];
                maxLeft = Math.max(maxLeft, p[0].length);
                maxMiddle                       = Math.max(maxMiddle, p[1].length);
                lines.push(p);
            }
            let left   = utils.align(maxLeft);
            let middle = utils.align(maxMiddle);
            for (let l of lines) {
                attrBuffer.push([utils.alignText(l[0], left), utils.alignText(l[1], middle), l[2]].join(''));
            }

            buffer.push(utils.addIndent(attrBuffer.join('\n'), 4))
        }
    }

    if (Object.keys(klass.static_methods).length > 0) {
        // export methods
        {
            {
                let methodBuffer: string[] = [];
                methodBuffer.push(`// static methods list`);
                for (let attr in klass.static_methods) {
                    const m = klass.static_methods[attr];
                    if (attr.startsWith('operator')) continue;
                    methodBuffer.push(`${processMethod(m).join('\n')}`);
                }
                buffer.push(utils.addIndent(methodBuffer.join('\n'), 4))
            }
        }
    }

    if (Object.keys(klass.methods).length > 0) {
        // export methods
        {
            {
                let methodBuffer: string[] = [];
                methodBuffer.push(`// methods list`);
                for (let attr in klass.methods) {
                    const m = klass.methods[attr];
                    if (attr.startsWith('operator')) continue;
                    methodBuffer.push(`${processMethod(m).join('\n')}`);
                }
                buffer.push(utils.addIndent(methodBuffer.join('\n'), 4))
            }
        }
    }


    buffer.push(`} // endof class ${klass.class_name}`);
    return buffer.join('\n');
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

for (let ns of exportNamespaces) {
    let klist = nsToClass[ns];
    if(!klist) {
        console.error(`namespace ${ns} not found!`)
    }
    topBuffer.push(`declare namespace ${ns} {`);
    topBuffer.push(utils.addIndent(klist.map(processClass).join('\n'), 4));
    topBuffer.push(`} // endof namespace ${ns}\n`);
}



fs.writeFileSync(outFile, topBuffer.join('\n'));

fs.writeFileSync(outFile, `\n\n\n/////// ${all_classes.length} classes process!\n`);

fs.closeSync(outFile);

{
    let finalFile = fs.openSync(copyTo, 'w');
    copyFiles.forEach(arr => fs.writeFileSync(finalFile, fs.readFileSync(arr).toString('utf8')));
    fs.closeSync(finalFile);
}

console.log(` -> ${all_classes.length}`);
