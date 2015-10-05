#include <boost/test/unit_test.hpp>
#include <envire_smurf/Robot.hpp>
#include <orocos_cpp/ConfigurationHelper.hpp>
#include <envire_core/graph/TransformGraph.hpp>
#include <envire_core/graph/GraphViz.hpp>

using namespace envire::smurf;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    envire::smurf::Robot robot;
    robot.welcome();
}

BOOST_AUTO_TEST_CASE(load_asguard_smurf)
{
    envire::smurf::Robot robot;
    std::string path = orocos_cpp::ConfigurationHelper::applyStringVariableInsertions("<%=ENV(AUTOPROJ_CURRENT_ROOT) %>/<%=ENV(ASGUARD4)%>");
    std::cout << "Path to robot model " << path << std::endl;
    envire::core::TransformGraph transformGraph;
    robot.loadFromSmurf(transformGraph, path);
    envire::core::GraphViz viz;
    viz.write(transformGraph, "load_asguard_smurf.dot");
    // Load now the dynamic transformations information
    //envire::smurf::Environment environment;
    //environment.loadDynamicTransforms(transformGraph, "<%=ENV(AUTOPROJ_CURRENT_ROOT) %>/tools/envire_smurf/test/dynamicTransformations/simulatedAsguard.yml");
    //viz.write(transformGraph, "simulatedAsguard.dot");
}
