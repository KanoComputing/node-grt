#include "NodeKMeansQuantizer.h"
#include "NodeTimeSeriesClassificationData.h"
#include <GRT/GRT.h>

Nan::Persistent<v8::Function> NodeKMeansQuantizer::constructor;

NAN_MODULE_INIT(NodeKMeansQuantizer::Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("KMeansQuantizer").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "train", Train);
    Nan::SetPrototypeMethod(tpl, "quantize", Quantize);
    Nan::SetPrototypeMethod(tpl, "getFeatureVector", GetFeatureVector);
    Nan::SetPrototypeMethod(tpl, "clear", Clear);

    constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("KMeansQuantizer").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}

NodeKMeansQuantizer::NodeKMeansQuantizer() {
    kmeansquantizer = new GRT::KMeansQuantizer();
}

NodeKMeansQuantizer::NodeKMeansQuantizer(const uint numClusters) {
    kmeansquantizer = new GRT::KMeansQuantizer(numClusters);
}

NodeKMeansQuantizer::~NodeKMeansQuantizer() {
}

NAN_METHOD(NodeKMeansQuantizer::Train) {
    v8::Isolate* isolate = info.GetIsolate();

    if (info.Length() < 1) {
        isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    NodeKMeansQuantizer* obj = Nan::ObjectWrap::Unwrap<NodeKMeansQuantizer>(info.This());
    NodeTimeSeriesClassificationData* data = Nan::ObjectWrap::Unwrap<NodeTimeSeriesClassificationData>(info[0]->ToObject());

    bool returnValue = obj->kmeansquantizer->train(*data->getTimeSeriesClassificationData());
    info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(NodeKMeansQuantizer::Quantize) {
    v8::Isolate* isolate = info.GetIsolate();

    if (info.Length() < 1) {
        isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    if (!info[0]->IsArray()) {
        isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, "Wrong argument")));
        return;
    }
    
    v8::Handle<v8::Array> vertice = v8::Handle<v8::Array>::Cast(info[0]);
    v8::Handle<v8::Value> verticeVal;
    double number;
    GRT::VectorFloat vector;
    for (unsigned int i = 0; i < vertice->Length(); i++) {
        verticeVal = vertice->Get(i);
        number = verticeVal->NumberValue();
        vector.push_back(number);
    }

    NodeKMeansQuantizer* obj = Nan::ObjectWrap::Unwrap<NodeKMeansQuantizer>(info.This());
    unsigned int rawReturn = obj->kmeansquantizer->quantize(vector);
    v8::Handle<v8::Number> returnValue = v8::Number::New(isolate, rawReturn);
    info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(NodeKMeansQuantizer::GetFeatureVector) {
    v8::Isolate* isolate = info.GetIsolate();
    NodeKMeansQuantizer* obj = Nan::ObjectWrap::Unwrap<NodeKMeansQuantizer>(info.This());
    GRT::VectorFloat vectorReturn = obj->kmeansquantizer->getFeatureVector();
    v8::Handle<v8::Array> returnValue = v8::Array::New(isolate, vectorReturn.getSize());
    for (unsigned int i = 0; i < vectorReturn.getSize(); i++) {
        v8::Handle<v8::Number> returnNum = v8::Number::New(isolate, vectorReturn[i]);
        returnValue->Set(i, returnNum);
    }
    info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(NodeKMeansQuantizer::Clear) {
    v8::Isolate* isolate = info.GetIsolate();
    NodeKMeansQuantizer* obj = Nan::ObjectWrap::Unwrap<NodeKMeansQuantizer>(info.This());
    bool returnValue = obj->kmeansquantizer->clear();
    info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(NodeKMeansQuantizer::New) {
    if (info.IsConstructCall()) {
        NodeKMeansQuantizer *obj = NULL;
        if (info.Length() == 1) {
            const uint numClusters = ( uint )( info[0]->Uint32Value() );
            obj = new NodeKMeansQuantizer(numClusters);
        } else {
            obj = new NodeKMeansQuantizer();
        }
        obj->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
    } else {
        v8::Local<v8::Function> cons = Nan::New(constructor);
        info.GetReturnValue().Set(cons->NewInstance());
    }
}
