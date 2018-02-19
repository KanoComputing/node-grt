var GRT = require('bindings')('GRT');

// HMM types to use for setHMMType method of HMM class
GRT.HMM_CONTINUOUS = 1; // default
GRT.HMM_DISCRETE = 0;

// Model types to use for setModelType method of HMM class
GRT.HMM_LEFTRIGHT = 1; // default
GRT.HMM_ERGODIC = 0;
module.exports = GRT;
