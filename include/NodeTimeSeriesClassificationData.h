#ifndef NODE_TIME_SERIES_CLASSIFICATION_DATA_H
#define NODE_TIME_SERIES_CLASSIFICATION_DATA_H

#include <nan.h>
#include <GRT/GRT.h>

class NodeTimeSeriesClassificationData : public Nan::ObjectWrap {
    public:
        static NAN_MODULE_INIT(Init);
        GRT::TimeSeriesClassificationData* getTimeSeriesClassificationData();

    private:
        explicit NodeTimeSeriesClassificationData();
        explicit NodeTimeSeriesClassificationData(const UINT numDimensions);
        ~NodeTimeSeriesClassificationData();

        static NAN_METHOD(New);
        static NAN_METHOD(SetNumDimensions);
        static NAN_METHOD(GetNumDimensions);
        static NAN_METHOD(SetDatasetName);
        static NAN_METHOD(SetInfoText);
        static NAN_METHOD(AddSample);
        static NAN_METHOD(GetNumSamples);
        static NAN_METHOD(Load);
        static NAN_METHOD(Save);
        static NAN_METHOD(Clear);
        static Nan::Persistent<v8::Function> constructor;
        GRT::TimeSeriesClassificationData *tscd;
};

#endif
