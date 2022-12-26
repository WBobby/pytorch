#define TORCH_ASSERT_ONLY_METHOD_OPERATORS
// ${generated_comment}

#include <ATen/core/LegacyTypeDispatch.h>
#include <ATen/FunctionalTensorWrapper.h>
#include <ATen/FunctionalInverses.h>
#include <torch/library.h>

#ifndef AT_PER_OPERATOR_HEADERS
#include <ATen/Operators.h>
#include <ATen/NativeFunctions.h>
#else
// needed for the meta tensor calls to get stride info in functionalization
#include <ATen/ops/empty_strided_native.h>
// needed for special handling of copy_().
// See Note [functionalizating copy_() and not preserving strides]
#include <ATen/ops/to_ops.h>
#include <ATen/ops/expand_copy_ops.h>

$ops_headers
#endif

namespace at {
namespace functionalization {


inline Tensor to_meta(const Tensor& t) {
    return at::native::empty_strided_meta(t.sizes(), t.strides(),
/*dtype=*/c10::make_optional(t.scalar_type()), /*layout=*/c10::make_optional(t.layout()),
/*device=*/c10::make_optional(c10::Device(kMeta)), /*pin_memory=*/c10::nullopt);
}

inline c10::optional<Tensor> to_meta(const c10::optional<Tensor>& t) {
  if (t.has_value()) {
    return c10::make_optional<Tensor>(to_meta(*t));
  }
  return c10::nullopt;
}

inline std::vector<Tensor> to_meta(const TensorList& t_list) {
  std::vector<Tensor> outputs(t_list.size());
  for (const auto i : c10::irange(t_list.size())) {
    outputs[i] = to_meta(t_list[i]);
  }
  return outputs;
}

inline c10::List<Tensor> to_meta(const c10::List<Tensor>& t_list) {
  c10::List<Tensor> outputs;
  outputs.reserve(t_list.size());
  for (const auto i : c10::irange(t_list.size())) {
    outputs.push_back(to_meta(t_list[i]));
  }
  return outputs;
}

inline c10::List<c10::optional<Tensor>> to_meta(const c10::List<c10::optional<Tensor>>& t_list) {
  c10::List<c10::optional<Tensor>> outputs;
  outputs.reserve(t_list.size());
  for (const auto i : c10::irange(t_list.size())) {
    outputs.push_back(to_meta(t_list[i]));
  }
  return outputs;
}


${func_definitions}

}  // namespace functionalization

namespace {

TORCH_LIBRARY_IMPL(aten, Functionalize, m) {
  ${func_registrations};
}

}  // namespace

} // namespace at