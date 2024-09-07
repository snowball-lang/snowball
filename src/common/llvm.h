
#include <llvm/ADT/DenseMap.h>
#include <llvm/ADT/StringMap.h>
#include <llvm/ADT/SmallVector.h>
#include <llvm/ADT/TinyPtrVector.h>

#include <llvm/Support/Threading.h>
#include <llvm/Support/ThreadPool.h>

namespace snowball {

template <typename K, typename V>
using DenseMap = llvm::DenseMap<K, V>;

template <typename K, typename V>
using StringMap = llvm::StringMap<V>;

template <typename T, unsigned N = 4>
using SmallVector = llvm::SmallVector<T, N>;

template <typename T>
using TinyPtrVector = llvm::TinyPtrVector<T>;

namespace threads {

using ThreadPool = ::llvm::ThreadPool;

/// Returns a thread strategy for tasks requiring significant memory or other
/// resources. To be used for workloads where hardware_concurrency() proves to
/// be less efficient. Avoid this strategy if doing lots of I/O. Currently
/// based on physical cores, if available for the host system, otherwise falls
/// back to hardware_concurrency(). Returns 1 when LLVM is configured with
/// LLVM_ENABLE_THREADS = OFF. 
inline auto HardwareStrategy(unsigned numThreads) {
  return llvm::hardware_concurrency(numThreads);
}

} // namespace threads
} // namespace snowball
