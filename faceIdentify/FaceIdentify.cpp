#include "FaceIdentify.h"
#include <opencv2\opencv.hpp>
#include <opencv2\face\facerec.hpp>
#include <range\v3\core.hpp>
#include <fstream>

namespace FaceIdentifion {

    const std::string FaceIdentify::scEigenModelPath = R"(F:\Projects\Windows\C++\VC\FaceDetectedIdentify\FaceDetectedIdentify\MyFacePCAModel.xml)";
    const std::string FaceIdentify::scFisherModelPath = R"(F:\Projects\Windows\C++\VC\FaceDetectedIdentify\FaceDetectedIdentify\MyFaceFisherModel.xml)";
    const std::string FaceIdentify::scLBPHModelPath = R"(F:\Projects\Windows\C++\VC\FaceDetectedIdentify\FaceDetectedIdentify\MyFaceLBPHModel.xml)";

    FaceIdentify::FaceIdentify()
    {
        {
            std::ifstream ifs(FaceIdentify::scEigenModelPath);

            if (ifs)
            {
                ifs.close();

                mEigenModel = cv::face::EigenFaceRecognizer::load<cv::face::EigenFaceRecognizer>(FaceIdentify::scEigenModelPath);

                if (mEigenModel == nullptr || mEigenModel.empty())
                {
                    mEigenModel = cv::face::EigenFaceRecognizer::create();
                }

                mbLoadEigen = true;
            }
        }


        {
            std::ifstream ifs(FaceIdentify::scFisherModelPath);

            if (ifs)
            {
                ifs.close();

                mFisherModel = cv::face::FisherFaceRecognizer::load<cv::face::FisherFaceRecognizer>(FaceIdentify::scFisherModelPath);

                if (mFisherModel == nullptr || mFisherModel.empty())
                {
                    mFisherModel = cv::face::FisherFaceRecognizer::create();
                }

                mbLoadFisher = true;
            }
        }


        {
            std::ifstream ifs(FaceIdentify::scLBPHModelPath);

            if (ifs)
            {
                ifs.close();
                mLBPModel = cv::face::LBPHFaceRecognizer::load<cv::face::LBPHFaceRecognizer>(FaceIdentify::scLBPHModelPath);

                if (mLBPModel == nullptr || mLBPModel.empty())
                {
                    mLBPModel = cv::face::LBPHFaceRecognizer::create();
                }

                mbLoadLBP = true;
            }
        }


    }


    FaceIdentify::~FaceIdentify()
    {
    }

    void FaceIdentify::trainEigenModel(std::vector<cv::Mat> faceImgs, std::vector<int> faceLabels)
    {
        if (mbLoadEigen)
        {
            mEigenModel->train(faceImgs, faceLabels);
        }
    }

    void FaceIdentify::trainFisherModel(std::vector<cv::Mat> faceImgs, std::vector<int> faceLabels)
    {
        if (mbLoadFisher)
        {
            mFisherModel->train(faceImgs, faceLabels);
        }
    }

    void FaceIdentify::trainLBPModel(std::vector<cv::Mat> faceImgs, std::vector<int> faceLabels)
    {
        if (mbLoadLBP)
        {
            mLBPModel->train(faceImgs, faceLabels);
        }
    }

    void FaceIdentify::saveModel()
    {
        if (mbLoadEigen)
        {
            mEigenModel->save(FaceIdentify::scEigenModelPath);
        }

        if (mbLoadFisher)
        {
            mFisherModel->save(FaceIdentify::scFisherModelPath);
        }

        if (mbLoadLBP)
        {
            mLBPModel->save(FaceIdentify::scLBPHModelPath);
        }
    }

    int FaceIdentify::predictEigenModel(cv::Mat faceImg)
    {
        if (mbLoadEigen)
        {
            return mEigenModel->predict(faceImg);
        }

        return -1;
    }

    int FaceIdentify::predictFisherModel(cv::Mat faceImg)
    {
        if (mbLoadFisher)
        {
            return mFisherModel->predict(faceImg);
        }

        return -1;
    }

    int FaceIdentify::predictLBPModel(cv::Mat faceImg)
    {
        if (mbLoadLBP)
        {
            return mLBPModel->predict(faceImg);
        }

        return -1;
    }

}
