const nativeExtension = require('../');
const assert = require('assert');
const { expect } = require('chai');
const fs = require('fs');

describe('TimeSeriesClassificationData', function() {
    let trainingData;
    before(() => {
        trainingData = new nativeExtension.TimeSeriesClassificationData();
    });

    after(() => {

        // Delete training data file after running the test
        fs.unlink('foo.grt', (err) => {
          if (err) throw err;
          console.log('Successfully deleted ../foo.grt');
        });
    });

    // setNumDimensions

    it('setNumDimensions should throw an error with wrong number of arguments', function() {
        expect(() => trainingData.setNumDimensions()).to.throw('Wrong number of arguments');
    });

    it('setNumDimensions should throw an error if argument is not an integer', function() {
        expect(() => trainingData.setNumDimensions(1.2)).to.throw('Wrong argument');
    });

    it('setNumDimensions should return true when calling the method with one integer argument', function() {
        assert.equal(trainingData.setNumDimensions(2), true);
    });

    // getNumDimensions

    it('getNumDimensions should return the right number for the dimensions if previously set', function() {
        assert.equal(trainingData.getNumDimensions(2), 2);
    });

    // setDatasetName

    it('setDatasetName should throw an error with wrong number of arguments', function() {
        expect(() => trainingData.setDatasetName()).to.throw('Wrong number of arguments');
    });

    it('setDatasetName should throw an error if argument is not a string', function() {
        expect(() => trainingData.setDatasetName(1)).to.throw('Wrong argument');
    });

    it('setDatasetName should return true when calling the method with one string argument', function() {
        expect(() => trainingData.setDatasetName(1)).to.throw('Wrong argument');
    });

    // setInfoText

    it('setInfoText should throw an error with wrong number of arguments', function() {
        expect(() => trainingData.setInfoText()).to.throw('Wrong number of arguments');
    });

    it('setInfoText should throw an error if argument is not a string', function() {
        expect(() => trainingData.setInfoText(1)).to.throw('Wrong argument');
    });

    it('setInfoText should return true when calling the method with one string argument', function() {
        expect(() => trainingData.setInfoText(1)).to.throw('Wrong argument');
    });

    // addSample

    it('addSample should throw an error with wrong number of arguments', function() {
        expect(() => trainingData.addSample('foo')).to.throw('Wrong number of arguments');
    });

    it('addSample should throw an error if first argument is not an integer', function() {
        expect(() => trainingData.addSample('foo', [])).to.throw('Wrong argument');
    });

    it('addSample should throw an error if second argument is not an array', function() {
        expect(() => trainingData.addSample(1, 'foo')).to.throw('Wrong argument');
    });

    it('addSample should throw an error if second argument is not a two-dimensional array', function() {
        expect(() => trainingData.addSample(1, [1])).to.throw('Wrong argument');
    });

    it('addSample should throw an error when the sample dimension is incorrect' , function() {
        expect(() => trainingData.addSample(1, [[1]])).to.throw('Incorrect dimension in sample');
    });

    it('addSample should return true when calling the method with one integer and one array arguments with the correct dimension', function() {
        assert.equal(trainingData.addSample(1, [[1, 2]]), true);
    });

    // save

    it('save should throw an error with wrong number of arguments', function() {
        expect(() => trainingData.save()).to.throw('Wrong number of arguments');
    });

    it('save should throw an error if argument is not a string', function() {
        expect(() => trainingData.save(1)).to.throw('Wrong argument');
    });

    it('save should return true when calling the method with one string argument', function() {
        assert.equal(trainingData.save('foo.grt'), true);
    });

    // load

    it('load should throw an error with wrong number of arguments', function() {
        expect(() => trainingData.load()).to.throw('Wrong number of arguments');
    });

    it('load should throw an error if argument is not a string', function() {
        expect(() => trainingData.load(1)).to.throw('Wrong argument');
    });

    it('load should return true when calling the method with one string argument', function() {
        assert.equal(trainingData.load('foo.grt'), true);
    });

    // clear

    it('clear should empty the training data', function() {
        trainingData.clear();
        assert.equal(trainingData.getNumSamples(), 0);
    });
});

describe('DTW', function() {
    let trainingData;
    let timeWarpingAlgorithm;
    before(() => {
        timeWarpingAlgorithm = new nativeExtension.DTW();
        trainingData = new nativeExtension.TimeSeriesClassificationData();
        trainingData.setNumDimensions(2);
        trainingData.addSample(1, [[1, 2]]);
    });

    // train

    it('train should throw an error with wrong number of arguments', function() {
        expect(() => timeWarpingAlgorithm.train()).to.throw('Wrong number of arguments');
    });

    it('train should return true when calling the method with a populated training data argument', function() {
        assert.equal(timeWarpingAlgorithm.train(trainingData), true);
    });

    // predict

    it('predict should throw an error with wrong number of arguments', function() {
        expect(() => timeWarpingAlgorithm.predict()).to.throw('Wrong number of arguments');
    });

    it('predict should throw an error if argument is not an array', function() {
        expect(() => timeWarpingAlgorithm.predict('foo', [])).to.throw('Wrong argument');
    });

    it('predict should throw an error if argument is not a two-dimensional array', function() {
        expect(() => timeWarpingAlgorithm.predict([1])).to.throw('Wrong argument');
    });

    it('predict should return true when calling the method with one array argument with the correct dimension', function() {
        assert.equal(timeWarpingAlgorithm.predict([[1, 2]]), true);
    });

    // getPredictedClassLabel

    it('getPredictedClassLabel should return the correct label', function() {
        assert.equal(timeWarpingAlgorithm.getPredictedClassLabel(), 1);
    });
    
    // getMaximumLikelihood

    it('getMaximumLikelihood should return 1 if sample and trainingData is a perfect match', function() {
        assert.equal(timeWarpingAlgorithm.getMaximumLikelihood(), 1);
    });
});
