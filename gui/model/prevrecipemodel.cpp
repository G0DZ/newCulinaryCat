#include "prevrecipemodel.h"

PrevRecipeModel::PrevRecipeModel(QObject * parent) : QObject(parent) {

}


QString PrevRecipeModel::getTitle() const
{
    return m_title;
}

void PrevRecipeModel::setTitle(const QString &value)
{
    m_title = value;
    emit titleChanged(m_title);
}

QString PrevRecipeModel::getImgLink() const
{
    return m_imgLink;
}

void PrevRecipeModel::setImgLink(const QString &value)
{
    m_imgLink = value;
    emit imgLinkChanged(m_imgLink);
}

QString PrevRecipeModel::getViews() const
{
    return m_views;
}

void PrevRecipeModel::setViews(const QString &value)
{
    m_views = value;
    emit viewsChanged(m_views);
}

QString PrevRecipeModel::getAuthorName() const
{
    return m_authorName;
}

void PrevRecipeModel::setAuthorName(const QString &value)
{
    m_authorName = value;
    emit authorNameChanged(m_authorName);
}

QString PrevRecipeModel::getRecipeDesc() const
{
    return m_recipeDesc;
}

void PrevRecipeModel::setRecipeDesc(const QString &value)
{
    m_recipeDesc = value;
    emit recipeDescChanged(m_recipeDesc);
}

QString PrevRecipeModel::getLikes() const
{
    return m_likes;
}

void PrevRecipeModel::setLikes(const QString &value)
{
    m_likes = value;
    emit likesChanged(m_likes);
}

QString PrevRecipeModel::getVotes() const
{
    return m_votes;
}

void PrevRecipeModel::setVotes(const QString &value)
{
    m_votes = value;
    emit votesChanged(m_votes);
}

QString PrevRecipeModel::getRecipeUrl() const
{
    return m_recipeUrl;
}

void PrevRecipeModel::setRecipeUrl(const QString &value)
{
    m_recipeUrl = value;
    emit recipeUrlChanged(m_recipeUrl);
}
