/*! \file bouncestudio.cpp  The whole of node-bouncestudio can be found here.
 * \mainpage
 *
 * \section synopsis Synopsis
 * This module provides a NodeJS wrapper to the BoogieTools BounceStudio API
 *
 * \section toc Table of Contents
 * - \ref license License
 * - \ref credits Credits
 * - \ref caveats Caveats
 *
 * \section license License
 * <div class="license">
 * Copyright (C) 2016 Dan Nielsen <dnielsen@reachmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * </div>
 *
 *
 * \section credits Credits
 * <div class="license">
 * Portability between NodeJS versions provided by nan 
 *   [ https://www.npmjs.com/package/nan ]
 * </div>
 *
 * \section caveats Caveats
 * <div class="license">
 * Please note that while this wrapper is provided under an open-source license
 * BoogieTools BounceStudio is not. It's license requires a subscription. For
 * more information see http://www.boogietools.com/Products/Linux/
 *
 */
#include <v8.h>
#include <nan.h>
#include <node.h>
#include <string.h>

#include "BounceStudio.h"

using namespace v8;
using namespace std;

/*!
 * \brief   Initializes bounce studio
 * \return  void
 *
 * Must be called once in the application to initialize BounceStudio.
 */
void BounceStudio_init (const Nan::FunctionCallbackInfo<v8::Value>& fn) {
  bsBounceStudio_init();
  fn.GetReturnValue().Set(Nan::Undefined());
}

/*! 
 * \brief   Checks a DSN via BounceStudio
 * \param   String  MessageText     Raw message to check
 * \param   String  EmailIgnoreList List of email addresses to ignore, pipe
 *                                  delimited.
 * \param   String  Key             License key
 * \return  Object                  BounceCheck result
 */
void BounceCheck (const Nan::FunctionCallbackInfo<v8::Value>& fn) {
  if (fn.Length() < 3) {
    Nan::ThrowError(
      Nan::Error("bsBounceCheck(MessageText, EmailIgnoreList, Key)"));
  }

  v8::String::Utf8Value _messageText(fn[0]->ToString());
  v8::String::Utf8Value _emailIgnoreList(fn[1]->ToString());
  v8::String::Utf8Value _key(fn[2]->ToString());

  char *__messageText     = *_messageText;
  char *__emailIgnoreList = *_emailIgnoreList;
  char *__key             = *_key;

  int   _bounceCode;
  char  *_emailAddress;

  _bounceCode = bsBounceCheck(__messageText, &_emailAddress, __emailIgnoreList,
    __key);

  v8::Local<v8::Object> _return = Nan::New<v8::Object>();

  Nan::Set(_return, Nan::New("bounceType").ToLocalChecked(),
    Nan::New(_bounceCode));

  switch (_bounceCode) {
    case 0:
      Nan::Set(_return, Nan::New("description").ToLocalChecked(),
        Nan::New("NON BOUNCE").ToLocalChecked());
      break;
    case 10:
      Nan::Set(_return, Nan::New("description").ToLocalChecked(),
        Nan::New("HARD BOUNCE").ToLocalChecked());
      break;
    case 20: 
      Nan::Set(_return, Nan::New("description").ToLocalChecked(),
        Nan::New("SOFT BOUNCE - General").ToLocalChecked());
      break;
    case 21:
      Nan::Set(_return, Nan::New("description").ToLocalChecked(),
        Nan::New("SOFT BOUNCE - Dns Failure").ToLocalChecked());
      break;
    case 22:
      Nan::Set(_return, Nan::New("description").ToLocalChecked(),
        Nan::New("SOFT BOUNCE - Mailbox Full").ToLocalChecked());
      break;
    case 23:
      Nan::Set(_return, Nan::New("description").ToLocalChecked(),
        Nan::New("SOFT BOUNCE - Message Size Too Large").ToLocalChecked());
      break;
    case 30:
      Nan::Set(_return, Nan::New("description").ToLocalChecked(),
        Nan::New("BOUNCE WITH NO EMAIL ADDRESS").ToLocalChecked());
      break;
    case 40:
      Nan::Set(_return, Nan::New("description").ToLocalChecked(),
        Nan::New("GENERAL BOUNCE").ToLocalChecked());
      break;
    case 50:
      Nan::Set(_return, Nan::New("description").ToLocalChecked(),
        Nan::New("MAIL BLOCK - General").ToLocalChecked());
      break;
    case 51:
      Nan::Set(_return, Nan::New("description").ToLocalChecked(),
        Nan::New("MAIL BLOCK - Known Spammer").ToLocalChecked());
      break;
    case 52:
      Nan::Set(_return, Nan::New("description").ToLocalChecked(),
        Nan::New("MAIL BLOCK - Spam Detected").ToLocalChecked());
      break;
    case 53:
      Nan::Set(_return, Nan::New("description").ToLocalChecked(),
        Nan::New("MAIL BLOCK - Attachment Detected").ToLocalChecked());
      break;
    case 54:
      Nan::Set(_return, Nan::New("description").ToLocalChecked(),
        Nan::New("MAIL BLOCK - Relay Denied").ToLocalChecked());
      break;
    case 60:
      Nan::Set(_return, Nan::New("description").ToLocalChecked(),
        Nan::New("AUTO REPLY").ToLocalChecked());
      break;
    case 70:
      Nan::Set(_return, Nan::New("description").ToLocalChecked(),
        Nan::New("TRANSIENT BOUNCE").ToLocalChecked());
      break;
    case 80:
      Nan::Set(_return, Nan::New("description").ToLocalChecked(),
        Nan::New("SUBSCRIBE REQUEST").ToLocalChecked());
      break;
    case 90:
      Nan::Set(_return, Nan::New("description").ToLocalChecked(),
        Nan::New("UNSUBSCRIBE REQUEST").ToLocalChecked());
      break;
    case 100:
      Nan::Set(_return, Nan::New("description").ToLocalChecked(),
        Nan::New("CHALLENGE RESPONSE").ToLocalChecked());
      break;
    default:
      Nan::Set(_return, Nan::New("description").ToLocalChecked(),
        Nan::Null());
      break;
  }
      
  if (!_emailAddress) {
    Nan::Set(_return, Nan::New("emailAddress").ToLocalChecked(), Nan::Null());
  } else {
    Nan::Set(_return, Nan::New("emailAddress").ToLocalChecked(), 
      Nan::New(_emailAddress).ToLocalChecked());
  }
  fn.GetReturnValue().Set(_return);
}

/*!
 * \brief   Returns the raw DSN
 * \param   String  MessageText   Raw DSN
 * \return  String                bsGetBody result
 */
void GetBody (const Nan::FunctionCallbackInfo<v8::Value>& fn) {
  if (fn.Length() < 1) {
    Nan::ThrowError(Nan::Error("bsGetBody(MessageText)"));
  }

  v8::String::Utf8Value _messageText(fn[0]->ToString());
  char *__messageText     = *_messageText;
  char *_body;

  bsGetBody(__messageText, &_body);

  v8::Local<v8::String> _return;

  if (!_body) {
    _return = Nan::New("").ToLocalChecked();
  } else {
    _return = Nan::New(_body).ToLocalChecked();
  }
  fn.GetReturnValue().Set(_return);
}
    
/*! 
 * \brief   Returns the DSN's RFC5322 From field
 * \param   String  MessageText     Raw DSN
 * \return  String                  DSN RFC5322 From field
 */
void GetFromAddress (const Nan::FunctionCallbackInfo<v8::Value>& fn) {
  if (fn.Length() < 1) {
    Nan::ThrowError(Nan::Error("bsGetFromAddress(MessageText)"));
  }

  v8::String::Utf8Value _messageText(fn[0]->ToString());
  char *__messageText   = *_messageText;
  char *_fromField;

  bsGetFromAddress(__messageText, &_fromField);

  v8::Local<v8::String> _return;

  if (!_fromField) {
    _return = Nan::New("").ToLocalChecked();
  } else {
    _return = Nan::New(_fromField).ToLocalChecked();
  }
  fn.GetReturnValue().Set(_return);
}
    
/*!
 * \brief   Returns the DSN's RFC5322 From field alias
 * \param   String  MessageText     Raw DSN
 * \return  String                  DSN RFC5322 From field alias
 */
void GetFromFriendlyName (const Nan::FunctionCallbackInfo<v8::Value>& fn) {
  if (fn.Length() < 1) {
    Nan::ThrowError(Nan::Error("bsGetFromFriendlyName(MessageText)"));
  }

  v8::String::Utf8Value _messageText(fn[0]->ToString());
  char *__messageText   = *_messageText;
  char *_fromFieldAlias;

  bsGetFromFriendlyName(__messageText, &_fromFieldAlias);

  v8::Local<v8::String> _return;

  if (!_fromFieldAlias) {
    _return = Nan::New("").ToLocalChecked();
  } else {
    _return = Nan::New(_fromFieldAlias).ToLocalChecked();
  }
  fn.GetReturnValue().Set(_return);
}

/*!
 * \brief   Returns the full DSN headers from the provided message. Does not
 *          include the original message headers.
 * \param   String  MessageText     Raw DSN
 * \return  String                  DSN RFC2822 header fields
 */
void GetHeader (const Nan::FunctionCallbackInfo<v8::Value>& fn) {
  if (fn.Length() < 1) {
    Nan::ThrowError(Nan::Error("bsGetHeader(MessageText)"));
  }

  v8::String::Utf8Value _messageText(fn[0]->ToString());
  char *__messageText   = *_messageText;
  char *_header;

  bsGetHeader(__messageText, &_header);

  v8::Local<v8::String> _return;

  if (!_header) {
    _return = Nan::New("").ToLocalChecked();
  } else {
    _return = Nan::New(_header).ToLocalChecked();
  }
  fn.GetReturnValue().Set(_return);
}

/*!
 * \brief   Returns the DSN's ReplyTo field from the provided message.
 * \param   String    MessageText     Raw dSN
 * \return  String                    DSN RFC2822 ReplyTo field
 */
void GetReplyToAddress (const Nan::FunctionCallbackInfo<v8::Value>& fn) {
  if (fn.Length() < 1) {
    Nan::ThrowError(Nan::Error("bsGetReplyToAddress(MessageText)"));
  }

  v8::String::Utf8Value _messageText(fn[0]->ToString());
  char *__messageText   = *_messageText;
  char *_field;

  bsGetReplyToAddress(__messageText, &_field);

  v8::Local<v8::String> _return;

  if (!_field) {
    _return = Nan::New("").ToLocalChecked();
  } else {
    _return = Nan::New(_field).ToLocalChecked();
  }
  fn.GetReturnValue().Set(_return);
}

/*!
 * \brief   Returns the DSN's RFC5322 ReplyTo field alias
 * \param   String  MessageText     Raw DSN
 * \return  String                  DSN RFC5322 ReplyTo field alias
 */
void GetReplyToFriendlyName (const Nan::FunctionCallbackInfo<v8::Value>& fn) {
  if (fn.Length() < 1) {
    Nan::ThrowError(Nan::Error("bsGetReplyToFriendlyName(MessageText)"));
  }

  v8::String::Utf8Value _messageText(fn[0]->ToString());
  char *__messageText   = *_messageText;
  char *_field;

  bsGetReplyToFriendlyName(__messageText, &_field);

  v8::Local<v8::String> _return;

  if (!_field) {
    _return = Nan::New("").ToLocalChecked();
  } else {
    _return = Nan::New(_field).ToLocalChecked();
  }
  fn.GetReturnValue().Set(_return);
}

/*!
 * \brief   Returns the DSN's RFC5322 Subject field alias
 * \param   String  MessageText     Raw DSN
 * \return  String                  DSN RFC5322 Subject field alias
 */
void GetSubject (const Nan::FunctionCallbackInfo<v8::Value>& fn) {
  if (fn.Length() < 1) {
    Nan::ThrowError(Nan::Error("bsGetSubject(MessageText)"));
  }

  v8::String::Utf8Value _messageText(fn[0]->ToString());
  char *__messageText   = *_messageText;
  char *_field;

  bsGetSubject(__messageText, &_field);

  v8::Local<v8::String> _return;

  if (!_field) {
    _return = Nan::New("").ToLocalChecked();
  } else {
    _return = Nan::New(_field).ToLocalChecked();
  }
  fn.GetReturnValue().Set(_return);
}

/*!
 * \brief   Returns the DSN's RFC5322 To field 
 * \param   String  MessageText     Raw DSN
 * \return  String                  DSN RFC5322 To field
 */
void GetToAddress (const Nan::FunctionCallbackInfo<v8::Value>& fn) {
  if (fn.Length() < 1) {
    Nan::ThrowError(Nan::Error("bsGetToAddress(MessageText)"));
  }

  v8::String::Utf8Value _messageText(fn[0]->ToString());
  char *__messageText   = *_messageText;
  char *_field;

  bsGetToAddress(__messageText, &_field);

  v8::Local<v8::String> _return;

  if (!_field) {
    _return = Nan::New("").ToLocalChecked();
  } else {
    _return = Nan::New(_field).ToLocalChecked();
  }
  fn.GetReturnValue().Set(_return);
}

/*!
 * \brief   Returns the DSN's RFC5322 To field alias
 * \param   String  MessageText     Raw DSN
 * \return  String                  DSN RFC5322 To field alias
 */
void GetToFriendlyName (const Nan::FunctionCallbackInfo<v8::Value>& fn) {
  if (fn.Length() < 1) {
    Nan::ThrowError(Nan::Error("bsGetToFriendlyName(MessageText)"));
  }

  v8::String::Utf8Value _messageText(fn[0]->ToString());
  char *__messageText   = *_messageText;
  char *_field;

  bsGetToFriendlyName(__messageText, &_field);

  v8::Local<v8::String> _return;

  if (!_field) {
    _return = Nan::New("").ToLocalChecked();
  } else {
    _return = Nan::New(_field).ToLocalChecked();
  }
  fn.GetReturnValue().Set(_return);
}

/*!
 * \brief   Returns the DSN's specified RFC5322 field
 * \param   String  MessageText     Raw DSN
 * \param   String  fieldName       Field name to extract, musr be lowercase
 * \return  String                  DSN RFC5322 field 
 */
void GetCustomHeader (const Nan::FunctionCallbackInfo<v8::Value>& fn) {
  if (fn.Length() < 2) {
    Nan::ThrowError(Nan::Error("bsGetCustomHeader(MessageText)"));
  }

  v8::String::Utf8Value _messageText(fn[0]->ToString());
  v8::String::Utf8Value _fieldName(fn[1]->ToString());
  char *__messageText   = *_messageText;
  char *__fieldName     = *_fieldName;
  char *_field;

  bsGetCustomHeader(__messageText, &_field, __fieldName);

  v8::Local<v8::String> _return;

  if (!_field) {
    _return = Nan::New("").ToLocalChecked();
  } else {
    _return = Nan::New(_field).ToLocalChecked();
  }
  fn.GetReturnValue().Set(_return);
}

/*!
 * \brief   Returns the original message's specified RFC5322 field
 * \param   String  MessageText     Raw DSN
 * \param   String  fieldName       Field name to extract, must be lowercase
 * \return  String                  DSN RFC5322 field 
 */
void GetOrigCustomHeader (const Nan::FunctionCallbackInfo<v8::Value>& fn) {
  if (fn.Length() < 2) {
    Nan::ThrowError(Nan::Error("bsGetCustomHeader(MessageText)"));
  }

  v8::String::Utf8Value _messageText(fn[0]->ToString());
  v8::String::Utf8Value _fieldName(fn[1]->ToString());
  char *__messageText   = *_messageText;
  char *__fieldName     = *_fieldName;
  char *_field;

  bsGetOrigCustomHeader(__messageText, &_field, __fieldName);

  v8::Local<v8::String> _return;

  if (!_field) {
    _return = Nan::New("").ToLocalChecked();
  } else {
    _return = Nan::New(_field).ToLocalChecked();
  }
  fn.GetReturnValue().Set(_return);
}


void InitAll(v8::Local<v8::Object> exports) {
  exports->Set(Nan::New("bsBounceStudio_init").ToLocalChecked(),
    Nan::New<v8::FunctionTemplate>(BounceStudio_init)->GetFunction());
  exports->Set(Nan::New("bsBounceCheck").ToLocalChecked(),
    Nan::New<v8::FunctionTemplate>(BounceCheck)->GetFunction());
  exports->Set(Nan::New("bsGetBody").ToLocalChecked(),
    Nan::New<v8::FunctionTemplate>(GetBody)->GetFunction());
  exports->Set(Nan::New("bsGetFromAddress").ToLocalChecked(),
    Nan::New<v8::FunctionTemplate>(GetFromAddress)->GetFunction());
  exports->Set(Nan::New("bsGetFromFriendlyName").ToLocalChecked(),
    Nan::New<v8::FunctionTemplate>(GetFromFriendlyName)->GetFunction());
  exports->Set(Nan::New("bsGetHeader").ToLocalChecked(),
    Nan::New<v8::FunctionTemplate>(GetHeader)->GetFunction());
  exports->Set(Nan::New("bsGetReplyToAddress").ToLocalChecked(),
    Nan::New<v8::FunctionTemplate>(GetReplyToAddress)->GetFunction());
  exports->Set(Nan::New("bsGetReplyToFriendlyName").ToLocalChecked(),
    Nan::New<v8::FunctionTemplate>(GetReplyToFriendlyName)->GetFunction());
  exports->Set(Nan::New("bsGetSubject").ToLocalChecked(),
    Nan::New<v8::FunctionTemplate>(GetSubject)->GetFunction());
  exports->Set(Nan::New("bsGetToAddress").ToLocalChecked(),
    Nan::New<v8::FunctionTemplate>(GetToAddress)->GetFunction());
  exports->Set(Nan::New("bsGetToFriendlyName").ToLocalChecked(),
    Nan::New<v8::FunctionTemplate>(GetToFriendlyName)->GetFunction());
  exports->Set(Nan::New("bsGetCustomHeader").ToLocalChecked(),
    Nan::New<v8::FunctionTemplate>(GetCustomHeader)->GetFunction());
  exports->Set(Nan::New("bsGetOrigCustomHeader").ToLocalChecked(),
    Nan::New<v8::FunctionTemplate>(GetOrigCustomHeader)->GetFunction());
}

NODE_MODULE(bouncestudio, InitAll)
    
