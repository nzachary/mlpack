#ifndef MLPACK_CORE_COOT_EXTEND_SERIALIZE_BANDICOOT_HPP
#define MLPACK_CORE_COOT_EXTEND_SERIALIZE_BANDICOOT_HPP

#if defined(MLPACK_HAS_COOT)

#include <cereal/archives/binary.hpp>
#include <cereal/archives/portable_binary.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/archives/json.hpp>

#include <mlpack/core/cereal/array_wrapper.hpp>

#include <bandicoot>

namespace cereal {

// Add an external serialization function for Mat.
template<typename Archive, typename eT>
void serialize(Archive& ar, coot::Mat<eT>& mat)
{
  arma::Mat<eT> armaMat;

  if (cereal::is_loading<Archive>())
  {
    ar(CEREAL_NVP(armaMat));
    mat = coot::conv_to<coot::Mat<eT>>::from(armaMat);
  }
  else
  {
    armaMat = coot::conv_to<arma::Mat<eT>>::from(mat);
    ar(CEREAL_NVP(armaMat));
  }
}

// Add a serialization function for Cube
template<typename Archive, typename eT>
void serialize(Archive& ar, coot::Cube<eT>& cube)
{
  arma::Cube<eT> armaCube;

  if (cereal::is_loading<Archive>())
  {
    ar(CEREAL_NVP(armaCube));
    cube = coot::conv_to<coot::Cube<eT>>::from(armaCube);
  }
  else
  {
    armaCube = coot::conv_to<arma::Cube<eT>>::from(cube);
    ar(CEREAL_NVP(armaCube));
  }
}

} // end namespace cereal

#endif // defined(MLPACK_HAS_COOT)

#endif // MLPACK_CORE_COOT_EXTEND_SERIALIZE_BANDICOOT_HPP
