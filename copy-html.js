var compressor = require('node-minify');
var path = require('path');
var fs = require('fs');

// Using Google Closure Compiler
compressor.minify({
    compressor: 'html-minifier',
    input: path.resolve(__dirname, 'assets/portal.html'),
    output: path.resolve(__dirname, 'assets/portal.minified.html'),
}).then((result) => {
    return `#include <Arduino.h>\nString htmlPortal="${result.replace(/\\n/g,'').replace(/"/g, "'")}";`
}).then((result) => fs.writeFile(path.resolve(__dirname, "src/assets/portal.hpp"), result, (res, err) => { }));
