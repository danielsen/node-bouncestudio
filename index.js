/* Copyright (C) 2016  Dan Nielsen <dnielsen@reachmail.com>
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
 */

const bouncestudio                = require('./build/Release/bouncestudio');

exports.bsBounceStudio_init       = bouncestudio.bsBounceStudio_init;
exports.bsBounceCheck             = bouncestudio.bsBounceCheck;
exports.bsGetBody                 = bouncestudio.bsGetBody;
exports.bsGetHeader               = bouncestudio.bsGetHeader;
exports.bsGetFromAddress          = bouncestudio.bsGetFromAddress;
exports.bsGetFromFriendlyName     = bouncestudio.bsGetFromFriendlyName;
exports.bsGetReplyToAddress       = bouncestudio.bsGetReplyToAddress;
exports.bsGetReplyToFriendlyName  = bouncestudio.bsGetReplyToFriendlyName;
exports.bsGetSubject              = bouncestudio.bsGetSubject;
exports.bsGetToAddress            = bouncestudio.bsGetToAddress;
exports.bsGetToFriendlyName       = bouncestudio.bsGetToFriendlyName;
exports.bsGetCustomHeader         = function (message, field) {
  return bouncestudio.bsGetCustomHeader(message, field.toLowerCase());
}
exports.bsGetOrigCustomHeader     = function (message, field) {
  return bouncestudio.bsGetOrigCustomHeader(message, field.toLowerCase());
}
