/**
 * @file bindings/julia/print_input_processing.hpp
 * @author Ryan Curtin
 *
 * Print Julia code to handle input arguments.
 *
 * mlpack is free software; you may redistribute it and/or modify it under the
 * terms of the 3-clause BSD license.  You should have received a copy of the
 * 3-clause BSD license along with mlpack.  If not, see
 * http://www.opensource.org/licenses/BSD-3-Clause for more information.
 */
#ifndef MLPACK_BINDINGS_JULIA_PRINT_INPUT_PROCESSING_HPP
#define MLPACK_BINDINGS_JULIA_PRINT_INPUT_PROCESSING_HPP

namespace mlpack {
namespace bindings {
namespace julia {

/**
 * Print the input processing (basically calling params.Get<>()) for a
 * non-serializable type.
 */
template<typename T>
void PrintInputProcessing(
    util::ParamData& d,
    const std::string& functionName,
    const std::enable_if_t<!arma::is_arma_type<T>::value>* = 0,
    const std::enable_if_t<!data::HasSerialize<T>::value>* = 0,
    const std::enable_if_t<!std::is_same_v<T,
        std::tuple<data::DatasetInfo, arma::mat>>>* = 0);

/**
 * Print the input processing for an Armadillo type.
 */
template<typename T>
void PrintInputProcessing(
    util::ParamData& d,
    const std::string& functionName,
    const std::enable_if_t<arma::is_arma_type<T>::value>* = 0,
    const std::enable_if_t<!std::is_same_v<T,
        std::tuple<data::DatasetInfo, arma::mat>>>* = 0);

/**
 * Print the input processing for a serializable type.
 */
template<typename T>
void PrintInputProcessing(
    util::ParamData& d,
    const std::string& functionName,
    const std::enable_if_t<!arma::is_arma_type<T>::value>* = 0,
    const std::enable_if_t<data::HasSerialize<T>::value>* = 0,
    const std::enable_if_t<!std::is_same_v<T,
        std::tuple<data::DatasetInfo, arma::mat>>>* = 0);

/**
 * Print the input processing (basically calling params.Get<>()) for a
 * matrix with DatasetInfo type.
 */
template<typename T>
void PrintInputProcessing(
    util::ParamData& d,
    const std::string& functionName,
    const std::enable_if_t<std::is_same_v<T,
        std::tuple<data::DatasetInfo, arma::mat>>>* = 0);

/**
 * Print the input processing (basically calling params.Get<>()) for a type.
 */
template<typename T>
void PrintInputProcessing(util::ParamData& d,
                          const void* input,
                          void* /* output */)
{
  // Call out to the right overload.
  PrintInputProcessing<std::remove_pointer_t<T>>(d, *((std::string*) input));
}

} // namespace julia
} // namespace bindings
} // namespace mlpack

#include "print_input_processing_impl.hpp"

#endif
