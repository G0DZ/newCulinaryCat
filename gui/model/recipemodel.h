#ifndef RECIPEMODEL_H
#define RECIPEMODEL_H

#include"prevrecipemodel.h"

class RecipeModel : public PrevRecipeModel
{
    Q_OBJECT
public:
    RecipeModel();
    QString publishDate() const;
    void setPublishDate(const QString &publishDate);
    Q_SIGNAL void publishDateChanged(const QString &);

    QString time() const;
    void setTime(const QString &time);
    Q_SIGNAL void timeChanged(const QString &);

    QString peaces() const;
    void setPeaces(const QString &peaces);
    Q_SIGNAL void peacesChanged(const QString &);
protected:
    QString m_publishDate;
    QString m_time;                           //время приготовления
    QString m_peaces;
};

#endif // RECIPEMODEL_H
