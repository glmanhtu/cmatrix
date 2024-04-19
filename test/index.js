var addon = require('bindings')('addon');
var assert = require('assert');

describe('native extension', function() {
    it('should export a wrapped object', function() {
        var obj = new addon.Matrix(10);
        assert.equal(obj.plusOne(), 11);
        assert.equal(obj.plusOne(), 12);
        assert.equal(obj.plusOne(), 13);
        assert.equal(obj.multiply().value(), 13);
        assert.equal(obj.multiply(10).value(), 130);

        var newobj = obj.multiply(-1);
        assert.equal(newobj.value(), -13);
    });
});
