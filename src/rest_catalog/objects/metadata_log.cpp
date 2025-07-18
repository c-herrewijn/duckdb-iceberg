
#include "rest_catalog/objects/metadata_log.hpp"

#include "yyjson.hpp"
#include "duckdb/common/string.hpp"
#include "duckdb/common/vector.hpp"
#include "duckdb/common/case_insensitive_map.hpp"
#include "rest_catalog/objects/list.hpp"

using namespace duckdb_yyjson;

namespace duckdb {
namespace rest_api_objects {

MetadataLog::MetadataLog() {
}
MetadataLog::Object4::Object4() {
}

MetadataLog::Object4 MetadataLog::Object4::FromJSON(yyjson_val *obj) {
	Object4 res;
	auto error = res.TryFromJSON(obj);
	if (!error.empty()) {
		throw InvalidInputException(error);
	}
	return res;
}

string MetadataLog::Object4::TryFromJSON(yyjson_val *obj) {
	string error;
	auto metadata_file_val = yyjson_obj_get(obj, "metadata-file");
	if (!metadata_file_val) {
		return "Object4 required property 'metadata-file' is missing";
	} else {
		if (yyjson_is_str(metadata_file_val)) {
			metadata_file = yyjson_get_str(metadata_file_val);
		} else {
			return StringUtil::Format("Object4 property 'metadata_file' is not of type 'string', found '%s' instead",
			                          yyjson_get_type_desc(metadata_file_val));
		}
	}
	auto timestamp_ms_val = yyjson_obj_get(obj, "timestamp-ms");
	if (!timestamp_ms_val) {
		return "Object4 required property 'timestamp-ms' is missing";
	} else {
		if (yyjson_is_sint(timestamp_ms_val)) {
			timestamp_ms = yyjson_get_sint(timestamp_ms_val);
		} else if (yyjson_is_uint(timestamp_ms_val)) {
			timestamp_ms = yyjson_get_uint(timestamp_ms_val);
		} else {
			return StringUtil::Format("Object4 property 'timestamp_ms' is not of type 'integer', found '%s' instead",
			                          yyjson_get_type_desc(timestamp_ms_val));
		}
	}
	return string();
}

MetadataLog MetadataLog::FromJSON(yyjson_val *obj) {
	MetadataLog res;
	auto error = res.TryFromJSON(obj);
	if (!error.empty()) {
		throw InvalidInputException(error);
	}
	return res;
}

string MetadataLog::TryFromJSON(yyjson_val *obj) {
	string error;
	if (yyjson_is_arr(obj)) {
		size_t idx, max;
		yyjson_val *val;
		yyjson_arr_foreach(obj, idx, max, val) {
			Object4 tmp;
			error = tmp.TryFromJSON(val);
			if (!error.empty()) {
				return error;
			}
			value.emplace_back(std::move(tmp));
		}
	} else {
		return StringUtil::Format("MetadataLog property 'value' is not of type 'array', found '%s' instead",
		                          yyjson_get_type_desc(obj));
	}
	return string();
}

} // namespace rest_api_objects
} // namespace duckdb
