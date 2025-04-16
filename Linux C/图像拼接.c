#if OPENCV_VERSION >= 3
#include <opencv2/stitching.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#else
#include <opencv2/stitching/stitcher.hpp>
#include <opencv2/stitching/warpers.hpp>
#endif

static Stitcher stitcher = Stitcher::createDefault(GPU_ENABLE);

/* opencv stitch configs */
static int stitcherConfig()
{
    stitcher.setRegistrationResol(0.8); // 默认是0.6,最大值1最慢，此方法用于特征点检测阶段，如果找不到特征点需要调高
    // stitcher.setSeamEstimationResol(0.1);//默认是0.1
    // stitcher.setCompositingResol(-1);//默认是-1，用于特征点检测阶段，找不到特征点的话，改-1
    stitcher.setPanoConfidenceThresh(1); // 默认是1
    stitcher.setWaveCorrection(false);   // 默认是true，false表示跳过WaveCorrection步骤
    // stitcher.setWaveCorrectKind(detail::WAVE_CORRECT_HORIZ);//还可以选detail::WAVE_CORRECT_VERT ,波段修正(wave correction)功能（水平方向/垂直方向修正）

    // Features matcher which finds two best matches for each feature and leaves the best one only if the ratio between descriptor distances is greater than the threshold match_conf.
    detail::BestOf2NearestMatcher *matcher = new detail::BestOf2NearestMatcher(false, 0.5f); // 默认是0.65，选太大了就没特征点
    stitcher.setFeaturesMatcher(matcher);

    // 找特征点surf算法，(计算量大,但对刚体运动、缩放、环境影响等情况下较为稳定)
    detail::SurfFeaturesFinder *featureFinder = new detail::SurfFeaturesFinder();
    stitcher.setFeaturesFinder(featureFinder);
    // 找特征点ORB算法
    // detail::OrbFeaturesFinder *featureFinder = new detail::OrbFeaturesFinder();
    // stitcher.setFeaturesFinder(featureFinder);

    // Rotation Estimation,It takes features of all images, pairwise matches between all images and estimates rotations of all cameras.
    // Implementation of the camera parameters refinement algorithm which minimizes sum of the distances between the rays passing through the camera center and a feature
    stitcher.setBundleAdjuster(new detail::BundleAdjusterRay());
    // Implementation of the camera parameters refinement algorithm which minimizes sum of the reprojection error squares.
    // stitcher.setBundleAdjuster(new detail::BundleAdjusterReproj());

    // Seam Estimation
    // Minimum graph cut-based seam estimator
    // stitcher.setSeamFinder(new detail::GraphCutSeamFinder(detail::GraphCutSeamFinderBase::COST_COLOR));
    // stitcher.setSeamFinder(new detail::GraphCutSeamFinder(detail::GraphCutSeamFinderBase::COST_COLOR_GRAD));//GraphCutSeamFinder的第二种形式
    // 啥SeamFinder也不用，Stub seam estimator which does nothing.
    stitcher.setSeamFinder(new detail::NoSeamFinder);
    // Voronoi diagram-based seam estimator.
    // stitcher.setSeamFinder(new detail::VoronoiSeamFinder);

    // exposure compensators曝光补偿
    // stitcher.setExposureCompensator(new detail::BlocksGainCompensator());
    // 不要曝光补偿
    stitcher.setExposureCompensator(new detail::NoExposureCompensator());
    // Exposure compensator which tries to remove exposure related artifacts by adjusting image intensities
    // stitcher.setExposureCompensator(new detail::detail::GainCompensator());
    // Exposure compensator which tries to remove exposure related artifacts by adjusting image block intensities
    // stitcher.setExposureCompensator(new detail::detail::BlocksGainCompensator());

    // Image Blenders
    // Blender which uses multi-band blending algorithm
    // stitcher.setBlender(new detail::MultiBandBlender(try_use_gpu));
    // Simple blender which mixes images at its borders
    stitcher.setBlender(new detail::FeatherBlender()); // 这个简单，耗时少

    // 柱面,球面,平面,默认为球面，选平面
    PlaneWarper *cw = new PlaneWarper();
    // SphericalWarper* cw = new SphericalWarper();
    // CylindricalWarper* cw = new CylindricalWarper();
    stitcher.setWarper(cw);

    return 0;
}

/* stitch img by opencv normal API*/
static int stitchNormalMode(int n, Mat *p, Mat &res)
{
    int i;
    vector<Mat> imgs;

    stitcherConfig();

    for (i = 0; i < n; i++)
    {
        dbg("stitch frame index=%d, p=%p\n", i, p);
        imgs.push_back(*(p++));
    }

    /*
    Stitcher::Status status = stitcher.estimateTransform(imgs);
    if (status != Stitcher::OK)
    {
        printf( "Can't estimateTransform images, error code %d\n " ,int(status) );
        return -1;
    }
    status = stitcher.composePanorama(*res);
    if (status != Stitcher::OK)
    {
        printf( "Can't composePanorama images, error code %d\n " ,int(status) );
        return -1;
    }
    */
    Stitcher::Status status = stitcher.stitch(imgs, res);
    if (status != Stitcher::OK)
    {
        err("Can't stitch images, error code = %d\n", int(status));
        return -1;
    }

    // TODO!!!!!!!        release memory
    return 0;
}