#ifndef NODE_K_MEANS_QUANTIZER_H
#define NODE_K_MEANS_QUANTIZER_H

#include <nan.h>
#include <GRT/GRT.h>

class NodeKMeansQuantizer : public Nan::ObjectWrap {
    public:
        static NAN_MODULE_INIT(Init);

    private:
        explicit NodeKMeansQuantizer();
        explicit NodeKMeansQuantizer(const UINT numClusters);
        ~NodeKMeansQuantizer();

        static NAN_METHOD(New);
        static NAN_METHOD(Train);
        static NAN_METHOD(Quantize);
        static NAN_METHOD(GetFeatureVector);
        static NAN_METHOD(Clear);
        
        static Nan::Persistent<v8::Function> constructor;
        GRT::KMeansQuantizer *kmeansquantizer;
};

#endif
