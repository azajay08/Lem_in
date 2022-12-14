import pygame
import os
import pygame.font

white = (255, 255, 255)
red = (255, 50, 50)
green = (100, 255, 100)
blue = (50, 100, 255)
orange1 = (255, 100, 0)
orange2 = (255, 160, 60)
orange3 = (255, 250, 150)

path = os.path.dirname(os.path.abspath(__file__))
tfont = os.path.join(path, 'fonts', 'ant_font.ttf')
ifont = os.path.join(path, 'fonts', 'Nugo.ttf')

class Title:
	"""A class to print the title and image"""

	def __init__(self, lv):
		"""Initialize title and image"""
		self.screen = lv.screen
		self.screen_rect = self.screen.get_rect()
		self.settings = lv.settings

		self.title_font = pygame.font.Font(tfont, 80)
		self.key_font = pygame.font.Font(ifont, 30)
		self.intsructions_font = pygame.font.Font(ifont, 25)
		
		title_str = "Lem_in"
		self.title = self.title_font.render(title_str, True,
					white, self.settings.bg_colour)
		self.title_rect = self.title.get_rect()
		self.title_rect.left = self.screen_rect.left + 80
		self.title_rect.top = self.screen_rect.top +30

		self.start_box = pygame.Surface((25, 25))
		self.start_box.fill(green)
		self.sink_box = pygame.Surface((25, 25))
		self.sink_box.fill(red)
		self.empty_room = pygame.Surface((25, 25))
		self.empty_room.fill(blue)
		self.ant_box1 = pygame.Surface((25, 25))
		self.ant_box1.fill(orange1)
		self.ant_box2 = pygame.Surface((25, 25))
		self.ant_box2.fill(orange2)
		self.ant_box3 = pygame.Surface((25, 25))
		self.ant_box3.fill(orange3)

		start_str = "Source"
		self.start = self.key_font.render(start_str, True,
					white, self.settings.bg_colour)
		sink_str = "Sink"
		self.sink = self.key_font.render(sink_str, True,
					white, self.settings.bg_colour)
		empty_str = "Empty room"
		self.empty = self.key_font.render(empty_str, True,
					white, self.settings.bg_colour)
		ant_str = "Ants"
		self.ant = self.key_font.render(ant_str, True,
					white, self.settings.bg_colour)
		up_down_str1 = "Press Up/Down arrow"
		self.up_down1 = self.intsructions_font.render(up_down_str1, True,
					white, self.settings.bg_colour)
		up_down_str2 = "keys to change flow speed"
		self.up_down2 = self.intsructions_font.render(up_down_str2, True,
					white, self.settings.bg_colour)
		space_str = "Press SPACE to pause"
		self.space = self.intsructions_font.render(space_str, True,
					white, self.settings.bg_colour)

		sink_count_str = "Ants in sink:"
		self.sink_count = self.intsructions_font.render(sink_count_str, True,
					white, self.settings.bg_colour)

		source_count_str = "Ants in source:"
		self.source_count = self.intsructions_font.render(source_count_str, True,
					white, self.settings.bg_colour)

	def draw_title_instructions(self):
		"""Draw instructions and title"""
		self.screen.blit(self.title, self.title_rect)
		self.screen.blit(self.start_box, (850, 50))
		self.screen.blit(self.sink_box, (850, 100))
		self.screen.blit(self.empty_room, (850, 150))
		self.screen.blit(self.ant_box1, (850, 200))
		self.screen.blit(self.ant_box2, (900, 200))
		self.screen.blit(self.ant_box3, (950, 200))
		self.screen.blit(self.start, (900, 50))
		self.screen.blit(self.sink, (900, 100))
		self.screen.blit(self.empty, (900, 150))
		self.screen.blit(self.ant, (1000, 200))
		self.screen.blit(self.up_down1, (70, 140))
		self.screen.blit(self.up_down2, (45, 170))
		self.screen.blit(self.space, (70, 210))
		self.screen.blit(self.source_count, (500, 95))
		self.screen.blit(self.sink_count, (500, 170))

		