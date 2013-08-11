
#ifndef template_alignment_h___
#define template_alignment_h___

#include "grasp_affordances/featurecloud.h"

#include <limits>
#include <vector>
#include <Eigen/Core>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/filters/passthrough.h>
#include <pcl/registration/ia_ransac.h>
	

class TemplateAlignment
{
  public:

    // A struct for storing alignment results
    struct Result
    {
      float fitness_score;
      Eigen::Matrix4f final_transformation;
      EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    };

    TemplateAlignment ();

    ~TemplateAlignment (){};

    // Set the given cloud as the target to which the templates will be aligned
    void setTargetCloud (FeatureCloud &target_cloud);

    // Add the given cloud to the list of template clouds
    void addTemplateCloud (FeatureCloud &template_cloud);

    // Align the given template cloud to the target specified by setTargetCloud ()
    void align (FeatureCloud &template_cloud, TemplateAlignment::Result &result);

    // Align all of template clouds set by addTemplateCloud to the target specified by setTargetCloud ()
    void alignAll (std::vector<TemplateAlignment::Result, Eigen::aligned_allocator<Result> > &results);

    // Align all of template clouds to the target cloud to find the one with best alignment score
    int findBestAlignment (TemplateAlignment::Result &result);

  private:
    // A list of template clouds and the target to which they will be aligned
    std::vector<FeatureCloud> templates_;
    FeatureCloud target_;

    // The Sample Consensus Initial Alignment (SAC-IA) registration routine and its parameters
    pcl::SampleConsensusInitialAlignment<pcl::PointXYZ, pcl::PointXYZ, pcl::FPFHSignature33> sac_ia_;
    float min_sample_distance_;
    float max_correspondence_distance_;
    int nr_iterations_;
};




#endif
