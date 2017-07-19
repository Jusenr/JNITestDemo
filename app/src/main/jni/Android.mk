# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

#include $(call all-subdir-makefiles)

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

# 要生成的so库的名称，但实际为libjniutils.so
LOCAL_MODULE := jniutils

#LOCAL_CPPFLAGS := -frtti -std=c++11

# 要使用的文件，刚才编写的JniUtilsTest.c文件
LOCAL_SRC_FILES := JniUtilsTest.c

#LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)