//
// Created by Chrystalkey on 30.09.2018.
//

#ifndef RAINCRAFT_PP_RESSOURCELOADER_H
#define RAINCRAFT_PP_RESSOURCELOADER_H


#include <QtCore/QHash>
#include <QtXml/QDomDocument>
#include <QtCore/QFile>
#include <QtCore/QMap>
#include <QImage>
#include <QList>

struct Texture{
    QImage texture;
    QString fileName;
    quint64 id;
};

struct BlockPrototype{
    QMap<QString,QString> attributes; //optimierbar
    std::vector<Texture*> textures;
};

class RessourceLoader{
public:
    RessourceLoader();
    ~RessourceLoader();
    bool parse_block_config(const QString &fileName);
private:
    void parseBlockElement(QDomElement *block);
    Texture *loadTexture(const QString &fileName);
private:
    QList<Texture*> allTextures;
    QHash<quint64,BlockPrototype> prototypes;
    quint64 blockID = 0, textureID = 0;
};


#endif //RAINCRAFT_PP_RESSOURCELOADER_H
