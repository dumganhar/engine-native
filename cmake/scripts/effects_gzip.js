const zlib = require('zlib');
const fs = require('fs');
const process = require('process');

if(process.argv.length != 5) {
    console.error('bad argument');
    console.error(' - input file');
    console.error(' - template file');
    console.error(' - output file');
    process.exit(-1);
}

const inputFile = process.argv[2];
const template = process.argv[3];
const outputFile = process.argv[4];

let encoded = zlib.gzipSync(fs.readFileSync(inputFile)).toString("base64");
let array = [];
let start = 0, last = encoded.length;
const charPerRow = 118;
while(start < last) {
    array.push(`"${encoded.substr(start, charPerRow)}"`);
    start += charPerRow;
}
encoded = array.join("\n");
let replaceData = fs.readFileSync(template).toString('utf-8').replace("${PLACE_HOLDER}", encoded);
fs.writeFileSync(outputFile, replaceData, {encoding: 'utf-8'});

process.exit(0);