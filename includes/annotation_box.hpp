#ifndef ANNOTATION_BOX_HPP
#define ANNOTATION_BOX_HPP

#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QCheckBox>
#include <QJsonObject>
#include <QPushButton>

#include "selection_box.hpp"

class AnnotationBox: public QGroupBox
{
    Q_OBJECT
public:
    // method
    AnnotationBox(qsizetype ith, QWidget* container, QWidget *parent = nullptr);

    std::shared_ptr<QJsonObject> annotation();
    void setAnnotation(QJsonObject const& data);

    qint16 index();
    void setIndex(qint16 index);

    bool isEmpty();

    ~AnnotationBox();

    // attributes
    QLineEdit* m_caption_line_edit = nullptr;

    QPushButton* m_add_button = nullptr;
    QPushButton* m_del_button = nullptr;

    QGroupBox* m_caption_group = nullptr;

    QVBoxLayout* m_caption_layout = nullptr;
    QHBoxLayout* m_button_layout = nullptr;
    QVBoxLayout* m_layout = nullptr;

    QJsonObject m_tmp_data;

signals:
    void contentChanged();

public slots:
    void handleCaptionChanged(QString const& question);

private:
    qint16 m_index;

};

#endif // ANNOTATION_BOX_HPP