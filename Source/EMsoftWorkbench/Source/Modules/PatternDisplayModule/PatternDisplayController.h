/* ============================================================================
* Copyright (c) 2009-2017 BlueQuartz Software, LLC
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* Redistributions of source code must retain the above copyright notice, this
* list of conditions and the following disclaimer.
*
* Redistributions in binary form must reproduce the above copyright notice, this
* list of conditions and the following disclaimer in the documentation and/or
* other materials provided with the distribution.
*
* Neither the name of BlueQuartz Software, the US Air Force, nor the names of its
* contributors may be used to endorse or promote products derived from this software
* without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* The code contained herein was partially funded by the followig contracts:
*    United States Air Force Prime Contract FA8650-07-D-5800
*    United States Air Force Prime Contract FA8650-10-D-5210
*    United States Prime Contract Navy N00173-07-C-2068
*
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#ifndef _patterndisplaycontroller_h_
#define _patterndisplaycontroller_h_



#include <QtCore/QObject>
#include <QtCore/QPair>
#include <QtCore/QSemaphore>
#include <QtCore/QThreadPool>
#include <QtCore/QFutureWatcher>
#include <QtGui/QImage>

#include "H5Support/QH5Lite.h"
#include "H5Support/QH5Utilities.h"
#include "H5Support/HDF5ScopedFileSentinel.h"

#include "Common/MasterPatternFileReader.h"
#include "Common/AbstractImageGenerator.h"
#include "Common/ProjectionConversionTask.h"

#include "SIMPLib/Math/SIMPLibMath.h"
#include "SIMPLib/Common/SIMPLibSetGetMacros.h"
#include "SIMPLib/DataArrays/DataArray.hpp"

#include "OrientationLib/Utilities/ModifiedLambertProjection.h"

#include "Modules/PatternDisplayModule/MPMCDisplayWidget.h"
#include "Modules/PatternDisplayModule/SimulatedPatternDisplayWidget.h"

class PatternDisplayController : public QObject
{
    Q_OBJECT

  public:
    PatternDisplayController(QObject *parent = nullptr);
    ~PatternDisplayController();

    SIMPL_INSTANCE_PROPERTY(SimulatedPatternDisplayWidget*, PatternDisplayWidget)
    SIMPL_INSTANCE_PROPERTY(IObserver*, Observer)

    struct DetectorData
    {
        double scintillatorDist;
        double detectorTiltAngle;
        double detectorOmegaAngle;
        double scintillatorPixelSize;
        double numOfPixelsX;
        double numOfPixelsY;
        double patternCenterX;
        double patternCenterY;
        double pixelCoordinateX;
        double pixelCoordinateY;
        double samplingStepSizeX;
        double samplingStepSizeY;
        double beamCurrent;
        double dwellTime;
        double barrelDistortion;
        double energyMin;
        double energyMax;
        QString masterFilePath;
    };

    /**
     * @brief validateDetectorValues
     * @param data
     * @return
     */
    bool validateDetectorValues(PatternDisplayController::DetectorData data);

    /**
     * @brief setMasterFilePath Sets a new master file.  Automatically reads the data from the master file
     * into the EMsoftController
     * @param masterFilePath
     */
    void setMasterFilePath(QString masterFilePath);

    typedef QPair<QVariant, QVariant> VariantPair;
    typedef QPair<float, float> FloatPair;
    typedef QPair<int, int> IntPair;

  public slots:
    /**
     * @brief generatePatternImage
     * @param patternData
     * @param detectorData
     */
    void generatePatternImages(SimulatedPatternDisplayWidget::PatternDisplayData patternData, PatternDisplayController::DetectorData detectorData);

    /**
     * @brief addPriorityIndex
     * @param index
     */
    void addPriorityIndex(size_t index);

  signals:
    void minMaxEnergyLevelsChanged(FloatArrayType::Pointer ekeVs);
    void mpImageNeedsDisplayed(GLImageViewer::GLImageData);
    void mcImageNeedsDisplayed(GLImageViewer::GLImageData);
    void energyMinChanged(int min);
    void energyMaxChanged(int max);
    void imageRangeChanged(int min, int max);
    void newProgressBarMaximumValue(int value);
    void newProgressBarValue(int value);
    void rowDataChanged(const QModelIndex &, const QModelIndex &);
    void mpmcGenerationFinished();
    void patternGenerationFinished();

    void errorMessageGenerated(const QString &msg);
    void warningMessageGenerated(const QString &msg);
    void stdOutputMessageGenerated(const QString &msg);

  private slots:
    void updateMPImage(MPMCDisplayWidget::MPMCData mpData);
    void updateMCImage(MPMCDisplayWidget::MPMCData mcData);

    void checkImageGenerationCompletion();

    void patternThreadFinished();

    void cancelGeneration();

  private:
    const QString                                     m_MasterLPNHName = "masterLPNH";
    const QString                                     m_MasterLPSHName = "masterLPSH";
    const QString                                     m_MasterCircleName = "masterCircle";
    const QString                                     m_MasterSPNHName = "masterSPNH";
    const QString                                     m_MonteCarloSquareName = "monteCarloSquare";
    const QString                                     m_MonteCarloCircleName = "monteCarloCircle";
    const QString                                     m_MonteCarloStereoName = "monteCarloStereo";

    QString                                           m_MasterFilePath;
    bool                                              m_Cancel = false;
    QSemaphore                                        m_NumOfFinishedPatternsLock;
    size_t                                            m_NumOfFinishedPatterns = 0;

    QList<size_t>                                     m_CurrentOrder;
    QList<size_t>                                     m_PriorityOrder;
    QSemaphore                                        m_CurrentOrderLock;

    MasterPatternFileReader::MasterPatternData          m_MP_Data;

    QVector<AbstractImageGenerator::Pointer>            m_MasterLPNHImageGenerators;
    QSemaphore                                          m_MasterLPNHImageGenLock;

    QVector<AbstractImageGenerator::Pointer>            m_MasterLPSHImageGenerators;
    QSemaphore                                          m_MasterLPSHImageGenLock;

    QVector<AbstractImageGenerator::Pointer>            m_MasterCircleImageGenerators;
    QSemaphore                                          m_MasterCircleImageGenLock;

    QVector<AbstractImageGenerator::Pointer>            m_MasterStereoImageGenerators;
    QSemaphore                                          m_MasterStereoImageGenLock;

    QVector<AbstractImageGenerator::Pointer>            m_MCSquareImageGenerators;
    QSemaphore                                          m_MCSquareImageGenLock;

    QVector<AbstractImageGenerator::Pointer>            m_MCCircleImageGenerators;
    QSemaphore                                          m_MCCircleImageGenLock;

    QVector<AbstractImageGenerator::Pointer>            m_MCStereoImageGenerators;
    QSemaphore                                          m_MCStereoImageGenLock;

    size_t                                            m_NumOfFinishedPatternThreads = 0;
    QVector< QSharedPointer<QFutureWatcher<void>> >   m_PatternWatchers;

    /**
     * @brief createMasterPatternImageGenerators Helper function that creates all the image generators for the master pattern images
     */
    void createMasterPatternImageGenerators();

    /**
     * @brief createMonteCarloImageGenerators Helper function that creates all the image generators for the monte carlo images
     */
    void createMonteCarloImageGenerators();

    /**
     * @brief createImageGeneratorTasks
     * @param data
     * @param xDim
     * @param yDim
     * @param zDim
     * @param imageGenerators
     * @param sem
     * @param horizontalMirror
     * @param verticalMirror
     */
    template <typename T>
    void createImageGeneratorTasks(typename DataArray<T>::Pointer data, size_t xDim, size_t yDim, size_t zDim,
                                   QVector<AbstractImageGenerator::Pointer> &imageGenerators, QSemaphore &sem, bool horizontalMirror = false, bool verticalMirror = false)
    {
      for (int z = 0; z < zDim; z++)
      {
        ImageGenerationTask<T>* task = new ImageGenerationTask<T>(data, xDim, yDim, z, imageGenerators, sem, z, horizontalMirror, verticalMirror);
        task->setAutoDelete(true);
        QThreadPool::globalInstance()->start(task);
      }
    }

    template <typename T, typename U>
    void createProjectionConversionTasks(typename DataArray<T>::Pointer data, size_t xDim, size_t yDim, size_t zDim, size_t projDim,
                                         ModifiedLambertProjection::ProjectionType projType, ModifiedLambertProjection::Square square,
                                         QVector<AbstractImageGenerator::Pointer> &imageGenerators, QSemaphore &sem, bool horizontalMirror = false,
                                         bool verticalMirror = false)
    {
      for (int z = 0; z < zDim; z++)
      {
        ProjectionConversionTask<T, U>* task = new ProjectionConversionTask<T, U>(data, xDim, yDim, projDim, projType,
                                                                                  0, square, imageGenerators, sem, z, horizontalMirror, verticalMirror);
        task->setAutoDelete(true);
        QThreadPool::globalInstance()->start(task);
      }
    }

    /**
     * @brief deHyperSlabData
     * @param data
     */
    template <typename T>
    typename DataArray<T>::Pointer deHyperSlabData(typename DataArray<T>::Pointer data, hsize_t xDim, hsize_t yDim, hsize_t zDim)
    {
      typename DataArray<T>::Pointer newData = std::dynamic_pointer_cast<DataArray<T>>(data->deepCopy());
      size_t currentIdx = 0;

      for (int z = 0; z < zDim; z++)
      {
        for (int y = yDim - 1; y >= 0; y--)   // We count down in the y-direction so that the image isn't flipped
        {
          for (int x = 0; x < xDim; x++)
          {
            int index = (xDim*zDim*y) + (zDim*x) + z;
            T value = data->getValue(index);
            newData->setValue(currentIdx, value);
            currentIdx++;
          }
        }
      }

      return newData;
    }

    /**
     * @brief generatePatternImagesUsingThread
     * @param patternData
     * @param detectorData
     * @param indexOrder
     */
    void generatePatternImagesUsingThread(SimulatedPatternDisplayWidget::PatternDisplayData patternData, PatternDisplayController::DetectorData detectorData);

    /**
     * @brief generatePatternImage
     * @param imageData
     * @param pattern
     * @param xDim
     * @param yDim
     * @param zValue
     * @return
     */
    bool generatePatternImage(GLImageViewer::GLImageData &imageData, FloatArrayType::Pointer pattern, hsize_t xDim, hsize_t yDim, hsize_t zValue);

    PatternDisplayController(const PatternDisplayController&);    // Copy Constructor Not Implemented
    void operator=(const PatternDisplayController&);  // Operator '=' Not Implemented
};

Q_DECLARE_METATYPE(PatternDisplayController::DetectorData)

#endif /* _patterndisplaycontroller_h_ */
