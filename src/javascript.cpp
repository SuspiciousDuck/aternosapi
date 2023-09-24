#include <cstring>
#include <string>
#include <algorithm>
#include <quickjs/quickjs.h>
#include "Javascript.hpp"

std::string Javascript::eval(std::string g) {
    JSRuntime *rt = JS_NewRuntime();
    JSContext *ctx = JS_NewContext(rt);
    JSValue result = JS_Eval(ctx, g.c_str(), strlen(g.c_str()), "<eval>", JS_EVAL_TYPE_GLOBAL);
    std::string result_string;
    
    if (!JS_IsException(result)) {
        const char *result_str = JS_ToCString(ctx, result);
        result_string = std::string(result_str);
        JS_FreeCString(ctx, result_str);
    }

    JS_FreeValue(ctx, result);
    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);

    return result_string;
}