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

#ifndef _patterndisplaywidget_h_
#define _patterndisplaywidget_h_

#include <QtCore/QObject>

#include "SIMPLib/Common/SIMPLibSetGetMacros.h"
#include "SIMPLib/DataArrays/DataArray.hpp"

#include "Common/GLImageViewer.h"

#include "ui_SimulatedPatternDisplayWidget.h"

class SimulatedPatternDisplayWidget : public QWidget, public Ui::SimulatedPatternDisplayWidget
{
    Q_OBJECT

  public:
    SimulatedPatternDisplayWidget(QWidget* parent = 0, Qt::WindowFlags windowFlags = Qt::WindowFlags());
    ~SimulatedPatternDisplayWidget();

    struct PatternDisplayData
    {
        size_t currentRow;
        size_t detectorBinningValue;
        QString patternOrigin;
        QString patternScaling;
        double gammaValue;
        bool useCircularMask;
        FloatArrayType::Pointer angles;
    };

    static const QString UpperLeftOrigin;
    static const QString LowerLeftOrigin;
    static const QString UpperRightOrigin;
    static const QString LowerRightOrigin;

    static const QString LinearScaling;
    static const QString GammaScaling;

    static const QString DetBin_1;
    static const QString DetBin_2;
    static const QString DetBin_4;
    static const QString DetBin_8;

    static const QString DetBinLabel;
    static const QString PatternOriginLabel;
    static const QString PatternScalingLabel;

    static const QString GenerateText;
    static const QString CancelText;

    /**
     * @brief setExpectedPatterns
     * @param eulerAngles
     */
    void setExpectedPatterns(FloatArrayType::Pointer eulerAngles);

    /**
     * @brief displayImage
     * @param imageData
     */
    void displayImage(GLImageViewer::GLImageData imageData);

    /**
     * @brief displayImage
     * @param index
     */
    void displayImage(int index);

    /**
     * @brief generateImage
     */
    void generateImages();

  public slots:
    /**
     * @brief loadImage
     * @param index
     * @param data
     */
    void loadImage(int index, GLImageViewer::GLImageData data);

    /**
     * @brief setProgressValue
     * @param value
     */
    void setProgressBarValue(int value);

    /**
     * @brief getDetectorBinningValue
     * @return
     */
    size_t getDetectorBinningValue();

    /**
     * @brief getPatternOrigin
     * @return
     */
    QString getPatternOriginValue();

    /**
     * @brief getPatternScaling
     * @return
     */
    QString getPatternScalingValue();

    /**
     * @brief getGammaValue
     * @return
     */
    double getGammaValue();

  protected:
    /**
     * @brief setupGui
     */
    void setupGui();

    /**
     * @brief closeEvent
     * @param event
     */
    void closeEvent(QCloseEvent *event);

  protected slots:
    /**
     * @brief on_slider_valueChanged
     * @param value
     */
    void on_gammaSpinBox_valueChanged(double value);

    /**
     * @brief on_useCircularMask_toggled
     * @param checked
     */
    void on_useCircularMask_toggled(bool checked);

    /**
     * @brief on_generateBtn_clicked
     */
    void on_generateBtn_clicked();

    /**
     * @brief on_saveBtn_clicked
     */
    void on_saveBtn_clicked();

    /**
     * @brief detectorBinning_selectionChanged
     */
    void detectorBinning_selectionChanged();

    /**
     * @brief patternOrigin_selectionChanged
     */
    void patternOrigin_selectionChanged();

    /**
     * @brief patternScaling_selectionChanged
     */
    void patternScaling_selectionChanged();

    /**
     * @brief patternListView_itemSelectionChanged
     * @param current
     * @param previous
     */
    void patternListView_itemSelectionChanged(const QItemSelection &current, const QItemSelection &previous);

    /**
     * @brief patternListView_doubleClicked
     */
    void patternListView_doubleClicked(const QModelIndex &index);

    /**
     * @brief setProgressBarMaximum
     * @param value
     */
    void setProgressBarMaximum(int value);

  signals:
    void dataChanged(SimulatedPatternDisplayWidget::PatternDisplayData patternData);
    void cancelRequested();
    void patternNeedsPriority(size_t index);
    void generationStarted();
    void generationFinished();

  private slots:
    void patternGenerationFinished();

  private:
    int                                                                             m_MinSBValue;
    int                                                                             m_MaxSBValue;

    QVector<GLImageViewer::GLImageData>                                      m_LoadedImageData;

    QActionGroup*                                                                   m_DetectorBinningMenuActionGroup = nullptr;
    QActionGroup*                                                                   m_PatternOriginMenuActionGroup = nullptr;
    QActionGroup*                                                                   m_PatternScalingMenuActionGroup = nullptr;

    QAction*                                                                            m_DetectorBinning_1 = nullptr;
    QAction*                                                                            m_DetectorBinning_2 = nullptr;
    QAction*                                                                            m_DetectorBinning_4 = nullptr;
    QAction*                                                                            m_DetectorBinning_8 = nullptr;

    QAction*                                                                            m_PatternOrigin_UL = nullptr;
    QAction*                                                                            m_PatternOrigin_LL = nullptr;
    QAction*                                                                            m_PatternOrigin_UR = nullptr;
    QAction*                                                                            m_PatternOrigin_LR = nullptr;

    QAction*                                                                            m_PatternScaling_Linear = nullptr;
    QAction*                                                                            m_PatternScaling_Gamma = nullptr;

    PatternDisplayData                                                                  m_CurrentPatternDisplayData;
    PatternDisplayData                                                                  m_NewPatternDisplayData;

    PatternDisplayData getPatternDisplayData();

    SimulatedPatternDisplayWidget(const SimulatedPatternDisplayWidget&);    // Copy Constructor Not Implemented
    void operator=(const SimulatedPatternDisplayWidget&);  // Operator '=' Not Implemented
};

Q_DECLARE_METATYPE(SimulatedPatternDisplayWidget::PatternDisplayData)

#endif /* _patterndisplaywidget_h_ */
