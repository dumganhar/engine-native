
import fs from "fs";
import path from "path";

const dir = path.normalize(path.join(__dirname, '../../../../cocos/bindings/auto'));
const jsonFiles = fs.readdirSync(dir).filter(x => x.endsWith(".json")).map(x => path.join(dir, x));


let all_classes = [];
for(let f of jsonFiles) {
    console.log(`require ${f}`);
    const content = fs.readFileSync(f).toString();
    if(content.length > 0) {
        all_classes = all_classes.concat(JSON.parse(content));
    }
}

console.log(all_classes.map(x => x.namespaced_class_name));

console.log(all_classes.length);



