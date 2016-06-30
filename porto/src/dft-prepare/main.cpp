#include <Soft>
#include <QtCore>
#include <cstring>
#include <cstdio>
#include <reference.hxx>
#include <file.hxx>

static soft::StdBlob toStdBlob(QByteArray const &bytes)
{
  soft::StdBlob blob(bytes.size());
  std::memcpy(blob.data(), bytes.constData(), bytes.size());
  return blob;
}

static soft::StdBlob dataFromFile(QString const &filename)
{
  QFile data(filename);
  QByteArray buffer;
  if (!data.open(QIODevice::ReadOnly)) {
    QTextStream(stderr) << "cannot open " << filename << endl;
  } else {
    buffer = data.readAll();
  }
  return toStdBlob(buffer);
}

int main(int argc, char **argv)
{
  ::soft::init(argc, argv); 
  if (argc < 3) {
    QTextStream(stderr) << "usage " << argv[0] << " <dft-data> <dft-bounday>" << endl;
  }

		
  auto &dftPath = argv[1]; // dft-path
  auto &dftBound = argv[2]; // remarc.in
  
  QFileInfo dftPathInfo(dftPath);
  soft::Reference reference;
  reference.uri          = dftPathInfo.absoluteFilePath().toStdString();
  reference.created      = dftPathInfo.created().toString("dd-mm-yyyy").toStdString();
  reference.owner        = dftPathInfo.owner().toStdString();
  reference.lastModified = dftPathInfo.lastModified().toString("dd-mm-yyyy").toStdString();  
  reference.sha1 = toStdBlob("0");

  QFileInfo dftBoundInfo(dftBound);
  soft::File file;
  file.filename          = dftBoundInfo.fileName().toStdString();
  file.suffix            = dftBoundInfo.suffix().toStdString();
  file.size              = dftBoundInfo.size();
  file.data              = dataFromFile(dftBoundInfo.absoluteFilePath());

  soft::Collection collection;
  collection.setName("DFTPrep");
  collection.setVersion("0.1");
  collection.attachEntity("dftPath", &reference);
  collection.attachEntity("dftBoundayFile", &file);
  
  freopen("mongo.log", "w", stdout);
  soft::Storage storage("mongo2", "mongodb://localhost", "db=porto;coll=demo");
  storage.save(&collection);

  fclose(stdout);
  stdout = fdopen(1, "w");
  QTextStream(stdout) << collection.id().c_str() << endl;
  return 0;
}
