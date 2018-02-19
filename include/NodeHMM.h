#ifndef NODE_HMM_H
#define NODE_HMM_H

#include <nan.h>
#include <GRT/GRT.h>

class NodeHMM : public Nan::ObjectWrap {
    public:
        static NAN_MODULE_INIT(Init);

    private:
        explicit NodeHMM();
        ~NodeHMM();

        static NAN_METHOD(New);
        static NAN_METHOD(Train);
        static NAN_METHOD(SetHMMType);
        static NAN_METHOD(SetNumStates);
        static NAN_METHOD(SetNumSymbols);
        static NAN_METHOD(SetModelType);
        static NAN_METHOD(SetMinChange);
        static NAN_METHOD(SetMaxNumEpochs);
        static NAN_METHOD(SetNumRandomTrainingIterations);
        static NAN_METHOD(Predict);
        static NAN_METHOD(GetPredictedClassLabel);
        static NAN_METHOD(GetClassLikelihoods);
        static Nan::Persistent<v8::Function> constructor;
        GRT::HMM *hmm;
};

#endif
