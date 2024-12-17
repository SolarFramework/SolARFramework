#ifndef IMAPEXPORTER_H
#define IMAPEXPORTER_H

#include <xpcf/api/IComponentIntrospect.h>
#include <xpcf/core/helpers.h>

#include "core/Messages.h"
#include "datastructure/Map.h"

namespace SolAR::api::output::files
{

/**
 * @class IMapExporter
 * @brief <B>Exports a map to a file.</B>
 * <TT>UUID: cfd06ac3-3c5f-418d-abdd-fc4c2858f584</TT>
 *
 */
class XPCF_IGNORE IMapExporter :
                                  virtual public org::bcom::xpcf::IComponentIntrospect {
public:
    IMapExporter() = default;
    virtual ~IMapExporter() = default;

    /// @brief Export a Map to a file
    /// @param[in] map: the map to export
    /// @return FrameworkReturnCode::_SUCCESS if export succeed, else FrameworkReturnCode::_ERROR_
    virtual FrameworkReturnCode exportMap(const SRef<SolAR::datastructure::Map> & map) = 0;
};

} // namespace SolAR::api::output::files


XPCF_DEFINE_INTERFACE_TRAITS(SolAR::api::output::files::IMapExporter,
                             "cfd06ac3-3c5f-418d-abdd-fc4c2858f584",
                             "IMapExporter",
                             "Export a map to a file");



#endif // IMAPEXPORTER_H
