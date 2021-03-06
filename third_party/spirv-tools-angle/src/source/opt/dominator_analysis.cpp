// Copyright (c) 2018 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "dominator_analysis.h"

#include <unordered_set>

#include "ir_context.h"

namespace spvtools {
namespace opt {

opt::BasicBlock* DominatorAnalysisBase::CommonDominator(
    opt::BasicBlock* b1, opt::BasicBlock* b2) const {
  if (!b1 || !b2) return nullptr;

  std::unordered_set<opt::BasicBlock*> seen;
  opt::BasicBlock* block = b1;
  while (block && seen.insert(block).second) {
    block = ImmediateDominator(block);
  }

  block = b2;
  while (block && !seen.count(block)) {
    block = ImmediateDominator(block);
  }

  return block;
}

bool DominatorAnalysisBase::Dominates(opt::Instruction* a,
                                      opt::Instruction* b) const {
  if (!a || !b) {
    return false;
  }

  if (a == b) {
    return true;
  }

  opt::BasicBlock* bb_a = a->context()->get_instr_block(a);
  opt::BasicBlock* bb_b = b->context()->get_instr_block(b);

  if (bb_a != bb_b) {
    return tree_.Dominates(bb_a, bb_b);
  }

  opt::Instruction* current_inst = a;
  while ((current_inst = current_inst->NextNode())) {
    if (current_inst == b) {
      return true;
    }
  }
  return false;
}

}  // namespace opt
}  // namespace spvtools
