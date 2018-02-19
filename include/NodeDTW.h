#ifndef NODE_DTW_H
#define NODE_DTW_H

#include <nan.h>
#include <GRT/GRT.h>

class NodeDTW : public Nan::ObjectWrap {
    public:
        static NAN_MODULE_INIT(Init);

    private:
        explicit NodeDTW();
        ~NodeDTW();

        static NAN_METHOD(New);
        static NAN_METHOD(Train);
        static NAN_METHOD(Predict);
        static NAN_METHOD(GetPredictedClassLabel);
        static NAN_METHOD(GetMaximumLikelihood);
        static Nan::Persistent<v8::Function> constructor;
        GRT::DTW *dtw;
};

#endif
