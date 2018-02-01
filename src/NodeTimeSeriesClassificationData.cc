#include "NodeTimeSeriesClassificationData.h"
#include <GRT/GRT.h>

Nan::Persistent<v8::Function> NodeTimeSeriesClassificationData::constructor;

NAN_MODULE_INIT(NodeTimeSeriesClassificationData::Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("TimeSeriesClassificationData").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    
    Nan::SetPrototypeMethod(tpl, "setNumDimensions", SetNumDimensions);
    Nan::SetPrototypeMethod(tpl, "getNumDimensions", GetNumDimensions);
    Nan::SetPrototypeMethod(tpl, "addSample", AddSample);
    Nan::SetPrototypeMethod(tpl, "save", Save);
    Nan::SetPrototypeMethod(tpl, "load", Load);

    constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("TimeSeriesClassificationData").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}

NodeTimeSeriesClassificationData::NodeTimeSeriesClassificationData() {
    tscd = new GRT::TimeSeriesClassificationData();
}

NodeTimeSeriesClassificationData::~NodeTimeSeriesClassificationData() {   
}

GRT::TimeSeriesClassificationData* NodeTimeSeriesClassificationData::getTimeSeriesClassificationData() {
    return tscd;
}


NAN_METHOD(NodeTimeSeriesClassificationData::SetNumDimensions) {
    v8::Isolate* isolate = info.GetIsolate();
    
    if (info.Length() < 1) {
        isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }
    
    if (!info[0]->IsNumber()) {
        isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, "Wrong argument")));
        return;
    }

    NodeTimeSeriesClassificationData* obj = Nan::ObjectWrap::Unwrap<NodeTimeSeriesClassificationData>(info.This());
    
    int dimensions = ( int )( info[0]->Int32Value() );
    bool returnValue = obj->tscd->setNumDimensions(dimensions);
    // std::cout << "Dimensions: " << dimensions << std::endl;
    info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(NodeTimeSeriesClassificationData::GetNumDimensions) {

    NodeTimeSeriesClassificationData* obj = Nan::ObjectWrap::Unwrap<NodeTimeSeriesClassificationData>(info.This());
    
    int returnValue = obj->tscd->getNumDimensions();
    std::cout << "Dimensions: " << returnValue << std::endl;
    info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(NodeTimeSeriesClassificationData::AddSample) {
    v8::Isolate* isolate = info.GetIsolate();
    
    if (info.Length() < 2) {
        isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }
    
    if (!info[0]->IsNumber()) {
        isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, "Wrong argument")));
        return;
    }
    
    NodeTimeSeriesClassificationData* obj = Nan::ObjectWrap::Unwrap<NodeTimeSeriesClassificationData>(info.This());

    if (!info[1]->IsArray()) {
        isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, "Wrong argument")));
        return;
    }
    int label = (int)(info[0]->Int32Value());
    GRT::MatrixFloat sample;
    v8::Handle<v8::Value> val;
    v8::Handle<v8::Value> itemVal;
    v8::Handle<v8::Array> item;
    v8::Handle<v8::Array> jsArray = v8::Handle<v8::Array>::Cast(info[1]);
    double number;
    GRT::VectorFloat vector;
    for (unsigned int i = 0; i < jsArray->Length(); i++) {
        val = jsArray->Get(i);
        if (!val->IsArray()) {
            isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, "Wrong argument")));
        }
        item = v8::Handle<v8::Array>::Cast(val);
        if (item->Length() != obj->tscd->getNumDimensions()) {
            isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, "Wrong argument")));
        }
        for (unsigned int j = 0; j < item->Length(); j++) {
            itemVal = item->Get(j);
            number = itemVal->NumberValue();
            vector.push_back(number);
        }
        sample.push_back(vector);
        vector.clear();
    }
    obj->tscd->addSample(label, sample);
}

NAN_METHOD(NodeTimeSeriesClassificationData::Load) {
    v8::Isolate* isolate = info.GetIsolate();
    
    if (info.Length() < 1) {
        isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }
    
    if (!info[0]->IsString()) {
        isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, "Wrong argument")));
        return;
    }
    
    v8::String::Utf8Value param1(info[0]->ToString());
    std::string fileName = std::string(*param1);
    
    NodeTimeSeriesClassificationData* obj = Nan::ObjectWrap::Unwrap<NodeTimeSeriesClassificationData>(info.This());
    bool returnValue = obj->tscd->load(fileName);
    std::cout << "Loading training data, success: " << std::boolalpha << returnValue << std::endl;
    info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(NodeTimeSeriesClassificationData::Save) {
    v8::Isolate* isolate = info.GetIsolate();
    
    if (info.Length() < 1) {
        isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }
    
    if (!info[0]->IsString()) {
        isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, "Wrong argument")));
        return;
    }
    
    v8::String::Utf8Value param1(info[0]->ToString());
    std::string fileName = std::string(*param1);
    
    NodeTimeSeriesClassificationData* obj = Nan::ObjectWrap::Unwrap<NodeTimeSeriesClassificationData>(info.This());
    bool returnValue = obj->tscd->save(fileName);
    std::cout << "Saving training data, success: " << std::boolalpha << returnValue << std::endl;
    info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(NodeTimeSeriesClassificationData::New) {
  if (info.IsConstructCall()) {
    NodeTimeSeriesClassificationData *obj = new NodeTimeSeriesClassificationData();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    v8::Local<v8::Function> cons = Nan::New(constructor);
    info.GetReturnValue().Set(cons->NewInstance());
  }
}