var addon = require('bindings')('cmatrix');
var assert = require('assert');

describe('native extension', function() {
    it('should export a wrapped object', function() {
        // var obj = new addon.Matrix(10);
        // assert.equal(obj.plusOne(), 11);
        // assert.equal(obj.plusOne(), 12);
        // assert.equal(obj.plusOne(), 13);
        // assert.equal(obj.multiply().value(), 13);
        // assert.equal(obj.multiply(10).value(), 130);

        // var newobj = obj.multiply(-1);
        // assert.equal(newobj.value(), -13);
        
        var rows = 10;
        var cols = 10;
        var arrObj = new addon.JMatrix(rows, cols, 0);

        // for (var i = 0 ; i < rows; i++) {
        //     for (var j = 0; j < cols; j++) {
        //         arrObj.setCell(i, j, (Math.random() * 5 | 0) + 6)
        //     }
        // }

        // var result = arrObj.mds(2, 50);
    });
});
