#include "material_library.h"
#include "qclsim-material.h"
#include "qclsim-material-property.h"
#include "qclsim-material-specification.h"
#include <glibmm/ustring.h>

/**
 * Default constructor
 */
MaterialSpecification::MaterialSpecification() :
    lib(new MaterialLibrary("")),
    valley(GAMMA),
    orientation(ORIENT_001),
    alloy(0.0),
    n3d(0.0)
{
    xml = new Material(lib->get_material("AlGaAs"));
}

/**
 * Specify a material by providing a list of properties
 */
MaterialSpecification::MaterialSpecification(const char          *mat_name,
                                             const Valley        &valley,
                                             const Orientation   &orientation,
                                             const double         alloy,
                                             const double         doping) :
    lib(new MaterialLibrary("")),
    valley(valley),
    orientation(orientation),
    alloy(alloy),
    n3d(doping)
{
    xml = new Material(lib->get_material(mat_name));
}
MaterialSpecification::MaterialSpecification(const Glib::ustring &mat_name,
                                             const Valley        &valley,
                                             const Orientation   &orientation,
                                             const double         alloy,
                                             const double         doping) :
    lib(new MaterialLibrary("")),
    valley(valley),
    orientation(orientation),
    alloy(alloy),
    n3d(doping)
{
    xml = new Material(lib->get_material(mat_name));
}

/**
 * Copy constructor
 *
 * \param[in] spec The material specification to be copied
 */
MaterialSpecification::MaterialSpecification(const MaterialSpecification &spec) :
    lib(new MaterialLibrary("")),
    valley(spec.valley),
    orientation(spec.orientation),
    alloy(spec.alloy),
    n3d(spec.n3d)
{
    std::string mat_name(spec.xml->get_name());
    xml = new Material(lib->get_material(mat_name));
}

MaterialSpecification::~MaterialSpecification()
{
    delete xml;
    delete lib;
}

MaterialSpecification & MaterialSpecification::operator=(const MaterialSpecification &rhs)
{
    lib    = new MaterialLibrary("");
    valley = rhs.valley;
    orientation = rhs.orientation;
    alloy  = rhs.alloy;
    n3d    = rhs.n3d;
    std::string mat_name(rhs.xml->get_name());
    xml    = new Material(lib->get_material(mat_name));

    return *this;
}

/**
 * Get the value of a property, using zero as the argument
 *
 * \param[in] prop_name The name of the property to look up
 *
 * \returns The value of the property
 */
double MaterialSpecification::get_prop_val_0(const char *prop_name) const
{
	Glib::ustring str(prop_name);
	return get_prop_val_0(str);
}

double MaterialSpecification::get_prop_val_0(Glib::ustring &prop_name) const
{
    return xml->get_property(prop_name)->get_val(0.0);
}

/**
 * Gets the text from a text property
 *
 * \param[in] prop_name The name of the property to look up
 *
 * \returns The text stored in the property
 */
const Glib::ustring & MaterialSpecification::get_prop_text(Glib::ustring &prop_name) const
{
    return xml->get_property(prop_name)->get_text();
}

const Glib::ustring & MaterialSpecification::get_prop_text(const char *prop_name) const
{
    Glib::ustring str(prop_name);
    return get_prop_text(str);
}

/**
 * Get the value of a property, using the alloy concentration
 * as the input parameter
 *
 * \param[in] prop_name The name of the property to look up
 *
 * \returns The value of the property
 */
double MaterialSpecification::get_prop_val_x(const char *prop_name) const
{
	Glib::ustring str(prop_name);
	return get_prop_val_x(str);
}

double MaterialSpecification::get_prop_val_x(Glib::ustring &prop_name) const
{
    return xml->get_property(prop_name)->get_val(alloy);
}
// vim: filetype=cpp:expandtab:shiftwidth=4:tabstop=8:softtabstop=4:fileencoding=utf-8:textwidth=99 :