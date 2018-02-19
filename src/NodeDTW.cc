#include "NodeDTW.h"
#include "NodeTimeSeriesClassificationData.h"
#include <GRT/GRT.h>

Nan::Persistent<v8::Function> NodeDTW::constructor;

NAN_MODULE_INIT(NodeDTW::Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("DTW").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "train", Train);
    Nan::SetPrototypeMethod(tpl, "predict", Predict);
    Nan::SetPrototypeMethod(tpl, "getPredictedClassLabel", GetPredictedClassLabel);
    Nan::SetPrototypeMethod(tpl, "getMaximumLikelihood", GetMaximumLikelihood);

    constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("DTW").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}

NodeDTW::NodeDTW() {
    dtw = new GRT::DTW();
}

NodeDTW::~NodeDTW() {
}

NAN_METHOD(NodeDTW::Train) {
    v8::Isolate* isolate = info.GetIsolate();

    if (info.Length() < 1) {
        isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    NodeDTW* obj = Nan::ObjectWrap::Unwrap<NodeDTW>(info.This());
    NodeTimeSeriesClassificationData* data = Nan::ObjectWrap::Unwrap<NodeTimeSeriesClassificationData>(info[0]->ToObject());

    bool returnValue = obj->dtw->train(*data->getTimeSeriesClassificationData());
    info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(NodeDTW::Predict) {
    v8::Isolate* isolate = info.GetIsolate();

    if (info.Length() < 1) {
        isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    NodeDTW* obj = Nan::ObjectWrap::Unwrap<NodeDTW>(info.This());
    if (!info[0]->IsArray()) {
        isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, "Wrong argument")));
        return;
    }
    GRT::MatrixFloat sample;
    v8::Handle<v8::Value> val;
    v8::Handle<v8::Value> itemVal;
    v8::Handle<v8::Array> item;
    v8::Handle<v8::Array> jsArray = v8::Handle<v8::Array>::Cast(info[0]);
    double number;
    GRT::VectorFloat vector;
    for (unsigned int i = 0; i < jsArray->Length(); i++) {
        val = jsArray->Get(i);
        if (!val->IsArray()) {
            isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, "Wrong argument")));
        }
        item = v8::Handle<v8::Array>::Cast(val);
        for (unsigned int j = 0; j < item->Length(); j++) {
            itemVal = item->Get(j);
            number = itemVal->NumberValue();
            vector.push_back(number);
        }
        sample.push_back(vector);
        vector.clear();
    }
    bool returnValue = obj->dtw->predict(sample);
    info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(NodeDTW::GetPredictedClassLabel) {
    NodeDTW* obj = Nan::ObjectWrap::Unwrap<NodeDTW>(info.This());
    int returnValue = obj->dtw->getPredictedClassLabel();
    std::cout << "Predicted class label: " << returnValue << std::endl;
    info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(NodeDTW::GetMaximumLikelihood) {
    NodeDTW* obj = Nan::ObjectWrap::Unwrap<NodeDTW>(info.This());
    double returnValue = obj->dtw->getMaximumLikelihood();
    std::cout << "Maximum Likelihood: " << returnValue << std::endl;
    info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(NodeDTW::New) {
  if (info.IsConstructCall()) {
    NodeDTW *obj = new NodeDTW();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    v8::Local<v8::Function> cons = Nan::New(constructor);
    info.GetReturnValue().Set(cons->NewInstance());
  }
}
