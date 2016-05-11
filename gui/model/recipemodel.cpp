#include "recipemodel.h"

RecipeModel::RecipeModel()
{

}

QString RecipeModel::publishDate() const
{
    return m_publishDate;
}

void RecipeModel::setPublishDate(const QString &publishDate)
{
    m_publishDate = publishDate;
    emit publishDateChanged(m_publishDate);
}

QString RecipeModel::time() const
{
    return m_time;
}

void RecipeModel::setTime(const QString &time)
{
    m_time = time;
    emit timeChanged(m_time);
}

QString RecipeModel::peaces() const
{
    return m_peaces;
}

void RecipeModel::setPeaces(const QString &peaces)
{
    m_peaces = peaces;
    emit peacesChanged(m_peaces);
}
