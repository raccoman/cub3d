#ifndef SOUND_H
# define SOUND_H

# include <SDL2/SDL.h>

# define MAXVOL 128
/*
 * Queue structure for all loaded sounds
 *
 */
typedef struct s_sound
{
	uint32_t		length;
	uint32_t		lengthTrue;
	uint8_t			*bufferTrue;
	uint8_t			*buffer;
	uint8_t			loop;
	uint8_t			fade;
	uint8_t			free;
	uint8_t			volume;
	SDL_AudioSpec	audio;
	struct t_audio	*next;
}					t_audio;

/*
 * Create a t_audio object
 *
 * @param filename      Filename for the WAVE file to load
 * @param loop          0 ends after playing once (sound),
 * 1 repeats and fades when other music added (music)
 * @param volume        Volume, read playSound()
 *
 * @return returns a new t_audio or NULL on failure,
 * you must call freeAudio() on return t_audio
 *
 */
t_audio	*createAudio(const char *filename, uint8_t loop, int volume);
/*
 * Frees as many chained Audios as given
 *
 * @param audio     Chain of sounds to free
 *
 */
void	freeAudio(t_audio *audio);
/*
 * Play a wave file currently must be S16LE format 2 channel stereo
 *
 * @param filename      Filename to open, use getAbsolutePath
 * @param volume        Volume 0 - 128. SDL_MIX_MAXVOLUME constant for max volume
 *
 */
void	playSound(const char *filename, int volume);
/*
 * Plays a new music, only 1 at a time plays
 *
 * @param filename      Filename of the WAVE file to load
 * @param volume        Volume read playSound for moree
 *
 */
void	playMusic(const char *filename, int volume);
/*
 * Plays a sound from a createAudio object (clones), only 1 at a time plays
 * Advantage to this method is no more disk reads,
 * only once, data is stored and constantly reused
 *
 * @param audio         t_audio object to clone and use
 * @param volume        Volume read playSound for moree
 */
void	playSoundFromMemory(t_audio *audio, int volume);
/*
 * Plays a music from a createAudio object (clones), only 1 at a time plays
 * Advantage to this method is no more disk reads,
 * only once, data is stored and constantly reused
 *
 * @param audio         t_audio object to clone and use
 * @param volume        Volume read playSound for moree
 */
void	playMusicFromMemory(t_audio *audio, int volume);
/*
 * Free all audio related variables
 * Note, this needs to be run even if initAudio fails,
 * because it frees the global audio device
 */
void	endAudio(void);
/*
 * Initialize t_audio Variable
 *
 */
void	initAudio(void);
/*
 * Pause audio from playing
 *
 */
void	pauseAudio(void);
/*
 * Unpause audio from playing
 *
 */
void	unpauseAudio(void);

#endif
