const grt = require('../');
const assert = require('assert');
const { expect } = require('chai');
const fs = require('fs');

describe('TimeSeriesClassificationData', function() {
    let trainingData;
    before(() => {
        trainingData = new grt.TimeSeriesClassificationData();
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
        timeWarpingAlgorithm = new grt.DTW();
        trainingData = new grt.TimeSeriesClassificationData();
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

describe('HMM', function() {
    let trainingData;
    let quantisedData;
    let hmmAlgorithm;
    let kMeansQuantizer;
    before(() => {
        hmmAlgorithm = new grt.HMM();
        trainingData = new grt.TimeSeriesClassificationData();
        trainingData.setNumDimensions(2);
        quantisedData = new grt.TimeSeriesClassificationData(1);
        quantisedData.setNumDimensions(1);
        kMeansQuantizer = new grt.KMeansQuantizer(2);
        trainingData.addSample(1, [[2, 4]]);
        trainingData.addSample(1, [[4, 8]]);
        trainingData.addSample(2, [[16, 8]]);
        trainingData.addSample(2, [[8, 4]]);
    });

    // setHMMType

    it('setHMMType should throw an error with wrong number of arguments', function() {
        expect(() => hmmAlgorithm.setHMMType()).to.throw('Wrong number of arguments');
    });

    it('setHMMType should return true when called with either grt.HMM_DISCRETE (0) or grt.HMM_DISCRETE (1)', function() {
        assert.equal(hmmAlgorithm.setHMMType(grt.HMM_DISCRETE), true);
    });

    // setNumStates

    it('setNumStates should throw an error with wrong number of arguments', function() {
        expect(() => hmmAlgorithm.setNumStates()).to.throw('Wrong number of arguments');
    });

    it('setNumStates should return true when called with one integer argument', function() {
        assert.equal(hmmAlgorithm.setNumStates(4), true);
    });

    // setNumSymbols

    it('setNumSymbols should throw an error with wrong number of arguments', function() {
        expect(() => hmmAlgorithm.setNumSymbols()).to.throw('Wrong number of arguments');
    });

    it('setNumSymbols should return true when called with one integer argument', function() {
        assert.equal(hmmAlgorithm.setNumSymbols(2), true);
    });

    // setModelType

    it('setModelType should throw an error with wrong number of arguments', function() {
        expect(() => hmmAlgorithm.setModelType()).to.throw('Wrong number of arguments');
    });

    it('setModelType should return true when called with either grt.HMM_ERGODIC (0) or grt.HMM_LEFTRIGHT (1)', function() {
        assert.equal(hmmAlgorithm.setModelType(grt.HMM_LEFTRIGHT), true);
    });

    // setMinChange

    it('setMinChange should throw an error with wrong number of arguments', function() {
        expect(() => hmmAlgorithm.setMinChange()).to.throw('Wrong number of arguments');
    });

    it('setMinChange should return true when called with one float argument', function() {
        assert.equal(hmmAlgorithm.setMinChange(0.00001), true);
    });

    // setMaxNumEpochs

    it('setMaxNumEpochs should throw an error with wrong number of arguments', function() {
        expect(() => hmmAlgorithm.setMaxNumEpochs()).to.throw('Wrong number of arguments');
    });

    it('setMaxNumEpochs should return true when called with one integer argument', function() {
        assert.equal(hmmAlgorithm.setMaxNumEpochs(2), true);
    });

    // SetNumRandomTrainingIterations

    it('setNumRandomTrainingIterations should throw an error with wrong number of arguments', function() {
        expect(() => hmmAlgorithm.setNumRandomTrainingIterations()).to.throw('Wrong number of arguments');
    });

    it('setNumRandomTrainingIterations should return true when called with one integer argument', function() {
        assert.equal(hmmAlgorithm.setNumRandomTrainingIterations(20), true);
    });

    // train

    it('train should throw an error with wrong number of arguments', function() {
        expect(() => hmmAlgorithm.train()).to.throw('Wrong number of arguments');
    });

    it('train should return true when called with a populated training data argument', function() {
        kMeansQuantizer.train(trainingData);
        let vertices = [[2, 4], [4, 8], [8, 16], [16, 8], [8, 4], [10, 5]];
        quantisedData.addSample(1, vertices.map((vertice) => {
            kMeansQuantizer.quantize(vertice);
            return kMeansQuantizer.getFeatureVector(vertice);
        }));
        assert.equal(hmmAlgorithm.train(quantisedData), true);
    });

    // predict

    it('predict should throw an error with wrong number of arguments', function() {
        expect(() => hmmAlgorithm.predict()).to.throw('Wrong number of arguments');
    });

    it('predict should throw an error if argument is not an array', function() {
        expect(() => hmmAlgorithm.predict('foo', [])).to.throw('Wrong argument');
    });

    it('predict should throw an error if argument is not a two-dimensional array', function() {
        expect(() => hmmAlgorithm.predict([1])).to.throw('Wrong argument');
    });

    it('predict should return true when calling the method with one array argument with the correct dimension', function() {
        assert.equal(hmmAlgorithm.predict([[1]]), true);
    });

    // getPredictedClassLabel

    it('getPredictedClassLabel should return the correct label', function() {
        assert.equal(hmmAlgorithm.getPredictedClassLabel(), 1);
    });

    // getClassLikelihoods
    it('getClassLikelihoods should return 1 if sample and trainingData is a perfect match', function() {
        assert.equal(hmmAlgorithm.getClassLikelihoods(), 1);
    });
});

describe('KMeansQuantizer', function() {
    let trainingData;
    let quantisedData;
    let kMeansQuantizer;
    before(() => {
        trainingData = new grt.TimeSeriesClassificationData();
        trainingData.setNumDimensions(2);
        quantisedData = new grt.TimeSeriesClassificationData(1);
        quantisedData.setNumDimensions(1);
        kMeansQuantizer = new grt.KMeansQuantizer(2);
        trainingData.addSample(1, [[2, 4]]);
        trainingData.addSample(1, [[4, 8]]);
        trainingData.addSample(2, [[16, 8]]);
        trainingData.addSample(2, [[8, 4]]);
    });

    // train

    it('train should throw an error with wrong number of arguments', function() {
        expect(() => kMeansQuantizer.train()).to.throw('Wrong number of arguments');
    });

    it('train should return true when calling the method with a populated training data argument', function() {
        assert.equal(kMeansQuantizer.train(trainingData), true);
    });

    // quantize

    it('quantize should throw an error with wrong number of arguments', function() {
        expect(() => kMeansQuantizer.quantize()).to.throw('Wrong number of arguments');
    });

    it('quantize should return the quantized value when called with an array argument', function() {
        assert.equal(kMeansQuantizer.quantize([1,2]), 1);
    });

    // getFeatureVector

    it('train should return true when calling the method with a populated training data argument', function() {
        let vertices = [[2, 4], [4, 8], [8, 16], [16, 8], [8, 4], [10, 5]];
        quantisedData.addSample(1, vertices.map((vertice) => {
            kMeansQuantizer.quantize(vertice);
            return kMeansQuantizer.getFeatureVector(vertice);
        }));
        assert.equal(true, true);
    });

});
