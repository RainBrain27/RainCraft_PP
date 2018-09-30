//
// Created by Chrystalkey on 30.09.2018.
//

#ifndef RAINCRAFT_PP_RESSOURCELOADER_H
#define RAINCRAFT_PP_RESSOURCELOADER_H


#include <QtCore/QHash>
#include <QtXml/QDomDocument>
#include <QtCore/QFile>
#include <QtCore/QMap>

class QImage;
struct BlockPrototype{
    QMap<QString,QString> attributes; //optimierbar
};

struct BlockTexture{
    QImage *t[];
};

class RessourceLoader{
public:
    RessourceLoader();
    ~RessourceLoader();
    bool parseBlockPrototypes(const QString &fileName);
    void parseBlockElement(QDomElement *block);
private:
    QHash<QString, BlockTexture> textures; // Blockname -> Texturenobjekt
    QHash<QString, BlockPrototype> blockAttributes;  //Blockname -> BlockPrototype Objekt
    QDomDocument xml;
    QFile xmlFile;
    quint64 blockID = 0, textureID = 0;
};


#endif //RAINCRAFT_PP_RESSOURCELOADER_H
