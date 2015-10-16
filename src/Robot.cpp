#include "Robot.hpp"
#include <iostream>
#include <smurf/Smurf.hpp>
#include <envire_core/items/Transform.hpp>
#include <base/Time.hpp>
#include <envire_core/items/Item.hpp>

void envire::envire_smurf::Robot::welcome()
{
    std::cout << "You successfully compiled and executed the envire_smurf Project. Welcome!" << std::endl;
}

void envire::envire_smurf::Robot::loadFromSmurf(envire::core::TransformGraph &graph, const std::string& path)
{
  // We want to be able to verify that every frame defined is connected through
  //some tranformation. That's why all the frames are included first
    smurf::Robot robot;
    robot.loadFromSmurf(path);
    // Frames
    std::vector<smurf::Frame *> frames= robot.getFrames();
    std::cout << "Iterate over the frames:" << std::endl;
    for(std::vector<smurf::Frame *>::iterator it = frames.begin(); it != frames.end(); ++it) {
//        base::Time time = base::Time::now();
//        base::TransformWithCovariance tf_cov;
//        envire::core::Transform envire_tf(time, tf_cov);
//        std::cout << "Include the following frame in the graph: " << (*it)->getName() << std::endl;
        // Make sure this method works 
        //graph.addFrame(frame->getName());
        //
        // By now we need: objects in that frame and type: link, joint (with
        // type) and sensor. This information goes in the config map of the
        // envire item
        //
        // Add an Item ConfigMap with this information to the frame
        //
        // Fill configMap with the node information and add it to the frame

        std::string frame_id = (*it)->getName();
        graph.addFrame(frame_id);

//////////////////////////////////////////////adding smurf collisions//////////////////////////////////////
        std::vector<smurf::Collidable> frame_collisons= (*it)->getCollisionObjects();
        boost::shared_ptr<envire::core::Item<std::vector<smurf::Collidable> > >collisons_itemPtr (new  envire::core::Item<std::vector<smurf::Collidable> > );
        collisons_itemPtr-> setData(frame_collisons);
        graph.addItemToFrame(frame_id, collisons_itemPtr);
//////////////////////////////////////////////adding smurf visuals//////////////////////////////////////
        std::vector<smurf::Visual> frame_visuals= (*it)->getVisuals();
        boost::shared_ptr<envire::core::Item<std::vector<smurf::Visual> > >visuals_itemPtr (new  envire::core::Item<std::vector<smurf::Visual> > );
        visuals_itemPtr-> setData(frame_visuals);
        graph.addItemToFrame(frame_id, visuals_itemPtr);




    }
    // Static Transformations: All transformations are considered static initially
    std::vector<smurf::StaticTransformation *> staticTfs= robot.getStaticTransforms();
    std::cout << " Static transformations " << std::endl;
    for(std::vector<smurf::StaticTransformation *>::iterator it = staticTfs.begin(); it != staticTfs.end(); ++it) {
        smurf::Frame source = (*it) -> getSourceFrame();
        envire::core::FrameId sourceId = source.getName();
        smurf::Frame target = (*it) -> getTargetFrame();
        envire::core::FrameId targetId = target.getName();
        Eigen::Affine3d tf_smurf = (*it) -> getTransformation();
        std::cout << "Transformation from " << sourceId <<" to " << targetId << " is " << tf_smurf.matrix() << std::endl;
        base::Time time = base::Time::now();
        base::TransformWithCovariance tf_cov(tf_smurf);
        envire::core::Transform envire_tf(time, tf_cov);
        graph.addTransform(sourceId, targetId, envire_tf);
    }
}
