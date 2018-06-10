/* Copyright 2016 The TensorFlow Authors. All Rights Reserved.

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 ==============================================================================*/

#include "tensorflow/cc/gradients/grad_testutil.h"

#include "tensorflow/cc/framework/grad_op_registry.h"

namespace tensorflow {
using namespace ops;
// NOLINT(build/namespaces)

namespace test {

Status CallGradFunction(const Scope& scope, const Operation& op,
		const std::vector<Output>& grad_inputs,
		std::vector<Output>* grad_outputs)
{
	GradFunc grad_fn;
	TF_RETURN_IF_ERROR(
			GradOpRegistry::Global()->Lookup(op.node()->type_string(),
					&grad_fn));
	TF_RETURN_IF_ERROR(grad_fn(scope, op, grad_inputs, grad_outputs));
	TF_RETURN_IF_ERROR(scope.status());
	return Status::OK();
}

}  // end namespace test
}  // end namespace tensorflow
