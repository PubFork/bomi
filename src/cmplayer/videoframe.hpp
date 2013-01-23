#ifndef VIDEOFRAME_HPP
#define VIDEOFRAME_HPP

#include "stdafx.hpp"
#include "videoformat.hpp"
extern "C" {
#include <video/mp_image.h>
}

struct mp_image;

class VideoFrame {
	VideoFrame(const VideoFrame&) = delete;
	VideoFrame &operator=(const VideoFrame&) = delete;
public:
	VideoFrame(): d(new Data) {}
	bool copy(const mp_image *mpi);
	bool copy(GLuint *texture, GLenum fmt);
	const VideoFormat &format() {return d->format;}
	void setFormat(const VideoFormat &format);
	QImage toImage() const;
	uchar *data(int i) {return reinterpret_cast<uchar*>(d->data[i].data());}
	const uchar *data(int i) const {return reinterpret_cast<const uchar*>(d->data[i].data());}
	inline void swap(VideoFrame &other) {d.swap(other.d);}
	inline quint32 id() const {return d->id;}
	void newId() {d->id = ++UniqueId;}
private:
	static quint32 UniqueId;
	struct Data : public QSharedData {
		Data() {}
		Data(const Data &other): QSharedData(other) {
			format = other.format;		data[0] = other.data[0];
			data[1] = other.data[1];	data[2] = other.data[2];
			id = other.id;
		}
		Data &operator = (const Data &rhs) = delete;
		VideoFormat format;
		QByteArray data[3];
		quint32 id = ++UniqueId;
	};
	QSharedDataPointer<Data> d;
};

#endif // VIDEOFRAME_HPP
