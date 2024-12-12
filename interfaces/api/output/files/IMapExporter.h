#ifndef IMAPEXPORTER_H
#define IMAPEXPORTER_H

#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/core/helpers.h>

#include "core/Messages.h"
#include "datastructure/Map.h"

namespace SolAR::api::output::files
{

/**
 * @class IMeshExporter
 * @brief <B>Exports a mesh to a file.</B>
 * <TT>UUID: faf50760-462c-11ed-b878-0242ac120002</TT>
 *
 */
class XPCF_IGNORE IMapExporter :
                                  virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    IMapExporter() = default;
    virtual ~IMapExporter() = default;

    /// @brief Export a Mesh to a file
    /// @param[in] mesh: the mesh to export
    /// @return FrameworkReturnCode::_SUCCESS if export succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode exportMap(const SRef<SolAR::datastructure::Map> & map) = 0;
};

} // namespace SolAR::api::output::files


XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::output::files::IMapExporter,
                             "cfd06ac3-3c5f-418d-abdd-fc4c2858f584",
                             "IMapExporter",
                             "Export a map to a file");



#endif // IMAPEXPORTER_H
