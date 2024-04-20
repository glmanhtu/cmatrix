var cmatrix = require('bindings')('cmatrix');

// var rows = 10;
// var cols = 10;
// var arrObj = new cmatrix.JMatrix(rows, cols, 0);

// for (var i = 0 ; i < rows; i++) {
//     for (var j = 0; j < cols; j++) {
//         arrObj.setCell(i, j, (Math.random() * 5 | 0) + 6)
//     }
// }

// var result = arrObj.mds(2, 50);
// console.log(result)

module.exports = cmatrix;