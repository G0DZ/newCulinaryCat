#ifndef PREVRECIPEMODEL_H
#define PREVRECIPEMODEL_H

#include <QObject>
#include <QStringList>

class PrevRecipeModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString titleTT NOTIFY titleChanged MEMBER m_title)
    Q_PROPERTY(QString imgLink NOTIFY imgLinkChanged MEMBER m_imgLink)
    Q_PROPERTY(QString views NOTIFY viewsChanged MEMBER m_views)
    Q_PROPERTY(QString authorName NOTIFY authorNameChanged MEMBER m_authorName)
    Q_PROPERTY(QString recipeDesc NOTIFY recipeDescChanged MEMBER m_recipeDesc)
    Q_PROPERTY(QString likes NOTIFY likesChanged MEMBER m_likes)
    Q_PROPERTY(QString votes NOTIFY votesChanged MEMBER m_votes)
    Q_PROPERTY(QString recipeUrl NOTIFY recipeUrlChanged MEMBER m_recipeUrl)
public:
    //констуктор
    Q_INVOKABLE PrevRecipeModel(QObject * parent = 0);

    QString getTitle() const;
    void setTitle(const QString &value);
    Q_SIGNAL void titleChanged(const QString &);

    QString getImgLink() const;
    void setImgLink(const QString &value);
    Q_SIGNAL void imgLinkChanged(const QString &);

    QString getViews() const;
    void setViews(const QString &value);
    Q_SIGNAL void viewsChanged(const QString &);

    QString getAuthorName() const;
    void setAuthorName(const QString &value);
    Q_SIGNAL void authorNameChanged(const QString &);

    QString getRecipeDesc() const;
    void setRecipeDesc(const QString &value);
    Q_SIGNAL void recipeDescChanged(const QString &);

    QString getLikes() const;
    void setLikes(const QString &value);
    Q_SIGNAL void likesChanged(const QString &);

    QString getVotes() const;
    void setVotes(const QString &value);
    Q_SIGNAL void votesChanged(const QString &);

    QString getRecipeUrl() const;
    void setRecipeUrl(const QString &value);
    Q_SIGNAL void recipeUrlChanged(const QString &);
private:
    QString m_title;                          //название
    QString m_imgLink;                        //картинка
    QString m_views;                          //просмотры
    QString m_authorName;                     //автор
    QString m_recipeDesc;                     //описание
    QString m_likes;                          //лайки
    QString m_votes;                          //голоса
    QString m_recipeUrl;                      //ссылка на рецепт
};

#endif // PREVRECIPEMODEL_H
