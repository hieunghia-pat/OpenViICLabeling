#include "annotation_box.hpp"
#include "annotation_widget.hpp"
#include "selection_box.hpp"

#include <QLabel>
#include <QString>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QJsonObject>
#include <QPair>
#include <QString>
#include <QPushButton>
#include <QIcon>

#include <memory>

AnnotationBox::AnnotationBox(qsizetype ith, QWidget* container, QWidget *parent)
    : QGroupBox{parent}
{
    m_index = ith;
    setTitle(QString("Annotation %1: ").arg(m_index+1));

    // Question-answer line editor
    m_caption_group = new QGroupBox();
    m_caption_group->setTitle("Caption: ");
    m_caption_line_edit = new QLineEdit();
    m_caption_layout = new QVBoxLayout(m_caption_group);
    m_caption_layout->addWidget(m_caption_line_edit);
    m_tmp_data["caption"] = m_caption_line_edit->text();

    // manipulation button
    m_add_button = new QPushButton();
    m_add_button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_add_button->setIcon(QIcon(":/media/icons/add.png"));
    m_del_button = new QPushButton();
    m_del_button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_del_button->setIcon(QIcon(":/media/icons/delete.png"));

    m_button_layout = new QHBoxLayout();
    m_button_layout->addWidget(m_add_button);
    m_button_layout->addWidget(m_del_button);
    m_button_layout->setAlignment(Qt::AlignRight);

    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(m_caption_group);
    m_layout->addLayout(m_button_layout);

    QObject::connect(m_add_button, &QPushButton::clicked, [container, this]() {
        static_cast<AnnotationWidget*>(container)->addAnnotation(this->m_index);
    });
    QObject::connect(m_del_button, &QPushButton::clicked, [container, this]() {
        static_cast<AnnotationWidget*>(container)->deleteAnnotation(this->m_index);
    });
    QObject::connect(m_caption_line_edit, &QLineEdit::textChanged, this, &AnnotationBox::handleCaptionChanged);
}

std::shared_ptr<QJsonObject> AnnotationBox::annotation()
{
    QString question = m_caption_line_edit->text();
    return std::make_shared<QJsonObject>(std::initializer_list<QPair<QString, QJsonValue>>{
        QPair<QString, QJsonValue>("caption", m_caption_line_edit->text())
    });
}

void AnnotationBox::setAnnotation(QJsonObject const& data)
{
    m_tmp_data = data;

    QString caption = data["caption"].toString();
    m_caption_line_edit->setText(caption);
}

qint16 AnnotationBox::index()
{
    return m_index;
}

void AnnotationBox::setIndex(qint16 index)
{
    m_index = index;
    setTitle(QString("Annotation %1").arg(m_index+1));
}

void AnnotationBox::handleCaptionChanged(QString const& question)
{
    if (question != m_tmp_data["caption"].toString())
        emit contentChanged();
}

bool AnnotationBox::isEmpty()
{
    return (m_caption_line_edit->text().isEmpty());
}

AnnotationBox::~AnnotationBox()
{

}