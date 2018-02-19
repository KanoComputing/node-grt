#include "NodeHMM.h"
#include "NodeTimeSeriesClassificationData.h"
#include <GRT/GRT.h>

Nan::Persistent<v8::Function> NodeHMM::constructor;

NAN_MODULE_INIT(NodeHMM::Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("HMM").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "setHMMType", SetHMMType);
    Nan::SetPrototypeMethod(tpl, "setNumStates", SetNumStates);
    Nan::SetPrototypeMethod(tpl, "setNumSymbols", SetNumSymbols);
    Nan::SetPrototypeMethod(tpl, "setModelType", SetModelType);
    Nan::SetPrototypeMethod(tpl, "setMinChange", SetMinChange);
    Nan::SetPrototypeMethod(tpl, "setMaxNumEpochs", SetMaxNumEpochs);
    Nan::SetPrototypeMethod(tpl, "setNumRandomTrainingIterations", SetNumRandomTrainingIterations);
    Nan::SetPrototypeMethod(tpl, "train", Train);
    Nan::SetPrototypeMethod(tpl, "predict", Predict);
    Nan::SetPrototypeMethod(tpl, "getPredictedClassLabel", GetPredictedClassLabel);
    Nan::SetPrototypeMethod(tpl, "getClassLikelihoods", GetClassLikelihoods);

    constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("HMM").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}

NodeHMM::NodeHMM() {
    hmm = new GRT::HMM();
}

NodeHMM::~NodeHMM() {
}

NAN_METHOD(NodeHMM::Train) {
    v8::Isolate* isolate = info.GetIsolate();

    if (info.Length() < 1) {
        isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    NodeHMM* obj = Nan::ObjectWrap::Unwrap<NodeHMM>(info.This());
    NodeTimeSeriesClassificationData* data = Nan::ObjectWrap::Unwrap<NodeTimeSeriesClassificationData>(info[0]->ToObject());

    bool returnValue = obj->hmm->train(*data->getTimeSeriesClassificationData());
    info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(NodeHMM::SetHMMType) {
    v8::Isolate* isolate = info.GetIsolate();

    if (info.Length() < 1) {
        std::string argsLength = std::to_string(info.Length());
        isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, ("Wrong number of arguments: expected 1, got " + argsLength).c_str())));
        return;
    }
    
    if (!info[0]->IsInt32()) {
        isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, "Wrong argument")));
        return;
    }

    NodeHMM* obj = Nan::ObjectWrap::Unwrap<NodeHMM>(info.This());
    
    int hmmType = ( int )( info[0]->Int32Value() );
    bool returnValue = obj->hmm->setHMMType(hmmType);
    info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(NodeHMM::SetNumStates) {
    v8::Isolate* isolate = info.GetIsolate();

    if (info.Length() < 1) {
        std::string argsLength = std::to_string(info.Length());
        isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, ("Wrong number of arguments: expected 1, got " + argsLength).c_str())));
        return;
    }
    
    if (!info[0]->IsInt32()) {
        isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, "Wrong argument")));
        return;
    }

    NodeHMM* obj = Nan::ObjectWrap::Unwrap<NodeHMM>(info.This());
    
    int numStates = ( int )( info[0]->Int32Value() );
    bool returnValue = obj->hmm->setNumStates(numStates);
    info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(NodeHMM::SetNumSymbols) {
    v8::Isolate* isolate = info.GetIsolate();

    if (info.Length() < 1) {
        std::string argsLength = std::to_string(info.Length());
        isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, ("Wrong number of arguments: expected 1, got " + argsLength).c_str())));
        return;
    }
    
    if (!info[0]->IsInt32()) {
        isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, "Wrong argument")));
        return;
    }

    NodeHMM* obj = Nan::ObjectWrap::Unwrap<NodeHMM>(info.This());
    
    int numSymbols = ( int )( info[0]->Int32Value() );
    bool returnValue = obj->hmm->setNumSymbols(numSymbols);
    info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(NodeHMM::SetModelType) {
    v8::Isolate* isolate = info.GetIsolate();

    if (info.Length() < 1) {
        std::string argsLength = std::to_string(info.Length());
        isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, ("Wrong number of arguments: expected 1, got " + argsLength).c_str())));
        return;
    }
    
    if (!info[0]->IsInt32()) {
        isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, "Wrong argument")));
        return;
    }

    NodeHMM* obj = Nan::ObjectWrap::Unwrap<NodeHMM>(info.This());
    
    int modelType = ( int )( info[0]->Int32Value() );
    bool returnValue = obj->hmm->setModelType(modelType);
    info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(NodeHMM::SetMinChange) {
    v8::Isolate* isolate = info.GetIsolate();

    if (info.Length() < 1) {
        std::string argsLength = std::to_string(info.Length());
        isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, ("Wrong number of arguments: expected 1, got " + argsLength).c_str())));
        return;
    }
    
    if (!info[0]->IsNumber()) {
        isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, "Wrong argument")));
        return;
    }

    NodeHMM* obj = Nan::ObjectWrap::Unwrap<NodeHMM>(info.This());
    
    int minChange = ( int )( info[0]->NumberValue() );
    bool returnValue = obj->hmm->setMinChange(minChange);
    info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(NodeHMM::SetMaxNumEpochs) {
    v8::Isolate* isolate = info.GetIsolate();

    if (info.Length() < 1) {
        std::string argsLength = std::to_string(info.Length());
        isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, ("Wrong number of arguments: expected 1, got " + argsLength).c_str())));
        return;
    }
    
    if (!info[0]->IsNumber()) {
        isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, "Wrong argument")));
        return;
    }

    NodeHMM* obj = Nan::ObjectWrap::Unwrap<NodeHMM>(info.This());
    
    int maxNumEpochs = ( int )( info[0]->NumberValue() );
    bool returnValue = obj->hmm->setMaxNumEpochs(maxNumEpochs);
    info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(NodeHMM::SetNumRandomTrainingIterations) {
    v8::Isolate* isolate = info.GetIsolate();

    if (info.Length() < 1) {
        std::string argsLength = std::to_string(info.Length());
        isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, ("Wrong number of arguments: expected 1, got " + argsLength).c_str())));
        return;
    }
    
    if (!info[0]->IsNumber()) {
        isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, "Wrong argument")));
        return;
    }

    NodeHMM* obj = Nan::ObjectWrap::Unwrap<NodeHMM>(info.This());
    
    int numRandomTrainingIterations = ( int )( info[0]->NumberValue() );
    bool returnValue = obj->hmm->setNumRandomTrainingIterations(numRandomTrainingIterations);
    info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(NodeHMM::Predict) {
    v8::Isolate* isolate = info.GetIsolate();

    if (info.Length() < 1) {
        isolate->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    NodeHMM* obj = Nan::ObjectWrap::Unwrap<NodeHMM>(info.This());
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
    bool returnValue = obj->hmm->predict(sample);
    info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(NodeHMM::GetPredictedClassLabel) {
    NodeHMM* obj = Nan::ObjectWrap::Unwrap<NodeHMM>(info.This());
    int returnValue = obj->hmm->getPredictedClassLabel();
    std::cout << "Predicted class label: " << returnValue << std::endl;
    info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(NodeHMM::GetClassLikelihoods) {
    v8::Isolate* isolate = info.GetIsolate();
    NodeHMM* obj = Nan::ObjectWrap::Unwrap<NodeHMM>(info.This());
    GRT::VectorFloat vectorReturn = obj->hmm->getClassLikelihoods();
    v8::Handle<v8::Array> returnValue = v8::Array::New(isolate, vectorReturn.getSize());
    for (unsigned int i = 0; i < vectorReturn.getSize(); i++) {
        v8::Handle<v8::Number> returnNum = v8::Number::New(isolate, vectorReturn[i]);
        returnValue->Set(i, returnNum);
    }
    info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(NodeHMM::New) {
    if (info.IsConstructCall()) {
        NodeHMM *obj = new NodeHMM();
        obj->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
    } else {
        v8::Local<v8::Function> cons = Nan::New(constructor);
        info.GetReturnValue().Set(cons->NewInstance());
    }
}
