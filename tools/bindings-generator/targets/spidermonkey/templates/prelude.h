#set generator = $current_class.generator

extern se::Object *__jsb_${current_class.underlined_class_name}_proto; // NOLINT
extern se::Class * __jsb_${current_class.underlined_class_name}_class; // NOLINT

bool js_register_${current_class.underlined_class_name}(se::Object *obj); // NOLINT
bool register_all_${generator.prefix}(se::Object *obj);                   // NOLINT

#if $current_class.is_struct
template <>
bool sevalue_to_native(const se::Value &, ${current_class.namespaced_class_name} *, se::Object *ctx);
#end if
JSB_REGISTER_OBJECT_TYPE(${current_class.namespaced_class_name});
