/*
* Copyright (c) 2011 Samsung Electronics Co., Ltd All Rights Reserved
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/


#include <tet_api.h>
#include <stdlib.h>
#include <metadata_extractor.h>

static void startup(void);
static void cleanup(void);

void (*tet_startup)(void) = startup;
void (*tet_cleanup)(void) = cleanup;


#define MEDIA_VIDEO_PATH		"/opt/usr/media/Videos/Color.mp4"
#define MEDIA_AUDIO_PATH		"/opt/usr/media/Sounds/Over the horizon.mp3"


#define READ_FROM_FILE(FILE_PATH, data, size) \
do{	\
	FILE * fp = fopen (FILE_PATH, "r");	\
	if (fp) {	\
			fseek (fp, 0, SEEK_END);	\
			size = ftell(fp);	\
			fseek (fp, 0, SEEK_SET);	\
			data = malloc (size);	\
			fread (data, size, sizeof(char), fp);	\
			fclose (fp);	\
			printf("file size = %d\n", size );	\
	}	\
}while(0)
#define SAFE_FREE(src)      { if(src) {free(src); src = NULL;}}


metadata_extractor_h g_metadata_h = NULL;


static void utc_metadata_extractor_create_n(void);
static void utc_metadata_extractor_create_p(void);
static void utc_metadata_extractor_set_path_n(void);
static void utc_metadata_extractor_set_path_p(void);
static void utc_metadata_extractor_set_buffer_n(void);
static void utc_metadata_extractor_set_buffer_p(void);
static void utc_metadata_extractor_destroy_n(void);
static void utc_metadata_extractor_destroy_p(void);
static void utc_metadata_extractor_get_metadata_n(void);
static void utc_metadata_extractor_get_metadata_p(void);
static void utc_metadata_extractor_get_artwork_n(void);
static void utc_metadata_extractor_get_artwork_p(void);
static void utc_metadata_extractor_get_frame_n(void);
static void utc_metadata_extractor_get_frame_p(void);
static void utc_metadata_extractor_get_frame_at_time_n(void);
static void utc_metadata_extractor_get_frame_at_time_p(void);
static void utc_metadata_extractor_get_synclyrics_n(void);
static void utc_metadata_extractor_get_synclyrics_p(void);


struct tet_testlist tet_testlist[] = {
	{ utc_metadata_extractor_create_n, 1 },
	{ utc_metadata_extractor_create_p, 1 },
	{ utc_metadata_extractor_set_path_n, 2 },
	{ utc_metadata_extractor_set_path_p, 2 },
	{ utc_metadata_extractor_get_metadata_n, 2 },
	{ utc_metadata_extractor_get_metadata_p, 2 },
	{ utc_metadata_extractor_get_artwork_n, 2 },
	{ utc_metadata_extractor_get_artwork_p, 2 },
	{ utc_metadata_extractor_get_frame_n, 2 },
	{ utc_metadata_extractor_get_frame_p, 2 },
	{ utc_metadata_extractor_get_synclyrics_n, 2 },
	{ utc_metadata_extractor_get_synclyrics_p, 2 },
	{ utc_metadata_extractor_get_frame_at_time_n, 2 },
	{ utc_metadata_extractor_get_frame_at_time_p, 2 },
	{ utc_metadata_extractor_set_buffer_n, 3 },
	{ utc_metadata_extractor_set_buffer_p, 3 },
	{ utc_metadata_extractor_destroy_n, 4 },
	{ utc_metadata_extractor_destroy_p, 4 },
	{ NULL, 0 },
};


static void startup(void)
{
	/* start of TC */
}


static void cleanup(void)
{
	/* end of TC */
}


/**
 * @brief Negative test case of metadata_extractor_create()
 */
static void utc_metadata_extractor_create_n(void)
{
	int ret = METADATA_EXTRACTOR_ERROR_NONE;

	ret = metadata_extractor_create(NULL);

	dts_check_eq("utc_metadata_extractor_create_n", ret, METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER, "Must return METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of metadata_extractor_create()
 */
static void utc_metadata_extractor_create_p(void)
{
	int ret = METADATA_EXTRACTOR_ERROR_NONE;

	ret = metadata_extractor_create(&g_metadata_h);

	dts_check_eq("utc_metadata_extractor_create_p", ret, METADATA_EXTRACTOR_ERROR_NONE, "Failed to create handle");
}

/**
 * @brief Negative test case of metadata_extractor_set_path()
 */
static void utc_metadata_extractor_set_path_n(void)
{
	int ret = METADATA_EXTRACTOR_ERROR_NONE;

	ret = metadata_extractor_set_path(NULL, MEDIA_VIDEO_PATH);

	dts_check_eq("utc_metadata_extractor_create_n", ret, METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER, "Must return METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of metadata_extractor_set_path()
 */
static void utc_metadata_extractor_set_path_p(void)
{
	int ret = METADATA_EXTRACTOR_ERROR_NONE;

	ret = metadata_extractor_set_path(g_metadata_h, MEDIA_VIDEO_PATH);

	dts_check_eq("utc_metadata_extractor_set_path_p", ret, METADATA_EXTRACTOR_ERROR_NONE, "Failed to set path");
}

/**
 * @brief Negative test case of metadata_extractor_set_buffer()
 */
static void utc_metadata_extractor_set_buffer_n(void)
{
	int ret = METADATA_EXTRACTOR_ERROR_NONE;

	ret = metadata_extractor_set_buffer(NULL, NULL, 0);

	dts_check_eq("utc_metadata_extractor_set_buffer_n", ret, METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER, "Must return METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of metadata_extractor_set_buffer()
 */
static void utc_metadata_extractor_set_buffer_p(void)
{
	void* buffer;
	long int size;
	int ret = METADATA_EXTRACTOR_ERROR_NONE;

	READ_FROM_FILE(MEDIA_AUDIO_PATH, buffer, size);

	ret = metadata_extractor_set_buffer(g_metadata_h, buffer, size);

	SAFE_FREE(buffer);

	dts_check_eq("utc_metadata_extractor_set_buffer_n", ret, METADATA_EXTRACTOR_ERROR_NONE, "Failed to set buffer");
}

/**
 * @brief Negative test case of metadata_extractor_get_metadata()
 */
static void utc_metadata_extractor_get_metadata_n(void)
{
	int ret = METADATA_EXTRACTOR_ERROR_NONE;
	char *value = NULL;

	ret = metadata_extractor_get_metadata(NULL, METADATA_TITLE, &value);

	dts_check_eq("utc_metadata_extractor_get_metadata_n", ret, METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER, "Must return METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of metadata_extractor_get_metadata()
 */
static void utc_metadata_extractor_get_metadata_p(void)
{
	int ret = METADATA_EXTRACTOR_ERROR_NONE;
	char *value = NULL;
	int idx = 0;

	for(idx = 0; idx < (METADATA_ROTATE + 1); idx++)
	{
		ret = metadata_extractor_get_metadata(g_metadata_h, idx, &value);
		SAFE_FREE(value);
		tet_printf("meta idx : [%d]\n", idx);
	}

	dts_check_eq("utc_metadata_extractor_get_metadata_p", ret, METADATA_EXTRACTOR_ERROR_NONE, "Failed to get metadata");
}

/**
 * @brief Negative test case of metadata_extractor_get_artwork()
 */
static void utc_metadata_extractor_get_artwork_n(void)
{
	int ret = METADATA_EXTRACTOR_ERROR_NONE;
	void *artwork = NULL;
	char *artwork_mime = NULL;
	int artwork_size = 0;

	ret = metadata_extractor_get_artwork(NULL, &artwork, &artwork_size, &artwork_mime);

	dts_check_eq("utc_metadata_extractor_get_artwork_n", ret, METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER, "Must return METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of metadata_extractor_get_artwork()
 */
static void utc_metadata_extractor_get_artwork_p(void)
{
	int ret = METADATA_EXTRACTOR_ERROR_NONE;
	metadata_extractor_h metadata = NULL;
	void *artwork = NULL;
	char *artwork_mime = NULL;
	int artwork_size = 0;

	ret = metadata_extractor_create(&metadata);
	ret = metadata_extractor_set_path(metadata, MEDIA_AUDIO_PATH);
	ret = metadata_extractor_get_artwork(metadata, &artwork, &artwork_size, &artwork_mime);

	SAFE_FREE(artwork);
	SAFE_FREE(artwork_mime);

	metadata_extractor_destroy(metadata);

	dts_check_eq("utc_metadata_extractor_get_artwork_p", ret, METADATA_EXTRACTOR_ERROR_NONE, "Failed to get artwork");
}

/**
 * @brief Negative test case of metadata_extractor_get_frame()
 */
static void utc_metadata_extractor_get_frame_n(void)
{
	int ret = METADATA_EXTRACTOR_ERROR_NONE;
	void *frame = NULL;
	int frame_size = 0;

	ret = metadata_extractor_get_frame(NULL, &frame, &frame_size);

	dts_check_eq("utc_metadata_extractor_get_frame_n", ret, METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER, "Must return METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of metadata_extractor_get_frame()
 */
static void utc_metadata_extractor_get_frame_p(void)
{
	int ret = METADATA_EXTRACTOR_ERROR_NONE;
	void *frame = NULL;
	int frame_size = 0;

	ret = metadata_extractor_get_frame(g_metadata_h, &frame, &frame_size);
	SAFE_FREE(frame);

	dts_check_eq("utc_metadata_extractor_get_frame_p", ret, METADATA_EXTRACTOR_ERROR_NONE, "Failed to get frame");
}

/**
 * @brief Negative test case of metadata_extractor_get_frame_at_time()
 */
static void utc_metadata_extractor_get_frame_at_time_n(void)
{
	int ret = METADATA_EXTRACTOR_ERROR_NONE;
	void *frame = NULL;
	int frame_size = 0;

	ret = metadata_extractor_get_frame_at_time(NULL, 0, true, &frame, &frame_size);

	dts_check_eq("utc_metadata_extractor_get_frame_at_time_n", ret, METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER, "Must return METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of metadata_extractor_get_frame_at_time()
 */
static void utc_metadata_extractor_get_frame_at_time_p(void)
{
	int ret = METADATA_EXTRACTOR_ERROR_NONE;
	void *frame = NULL;
	int frame_size = 0;

	ret = metadata_extractor_get_frame_at_time(g_metadata_h, 22500, true, &frame, &frame_size);
	SAFE_FREE(frame);

	dts_check_eq("utc_metadata_extractor_get_frame_at_time_p", ret, METADATA_EXTRACTOR_ERROR_NONE, "Failed to get frame");
}

/**
 * @brief Negative test case of metadata_extractor_get_synclyrics()
 */
static void utc_metadata_extractor_get_synclyrics_n(void)
{
	int ret = METADATA_EXTRACTOR_ERROR_NONE;
	unsigned long time_info = 0;
	char *lyrics = NULL;

	ret = metadata_extractor_get_synclyrics(NULL, 1, &time_info, &lyrics);

	dts_check_eq("utc_metadata_extractor_get_synclyrics_n", ret, METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER, "Must return METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of metadata_extractor_get_synclyrics()
 */
static void utc_metadata_extractor_get_synclyrics_p(void)
{
	int ret = METADATA_EXTRACTOR_ERROR_NONE;
	unsigned long time_info = 0;
	char *lyrics = NULL;

	ret = metadata_extractor_get_synclyrics(g_metadata_h, 1, &time_info, &lyrics);
	SAFE_FREE(lyrics);

	dts_check_eq("utc_metadata_extractor_get_synclyrics_p", ret, METADATA_EXTRACTOR_ERROR_NONE, "Failed to get lyrics");
}

/**
 * @brief Negative test case of metadata_extractor_destroy()
 */
static void utc_metadata_extractor_destroy_n(void)
{
	int ret = METADATA_EXTRACTOR_ERROR_NONE;

	ret = metadata_extractor_destroy(NULL);

	dts_check_eq("utc_metadata_extractor_destroy_n", ret, METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER, "Must return METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER in case of invalid parameter");
}

/**
 * @brief Positive test case of metadata_extractor_destroy()
 */
static void utc_metadata_extractor_destroy_p(void)
{
	int ret = METADATA_EXTRACTOR_ERROR_NONE;

	ret = metadata_extractor_destroy(g_metadata_h);

	dts_check_eq("utc_metadata_extractor_destroy_p", ret, METADATA_EXTRACTOR_ERROR_NONE, "Failed to destroy handle");
}

