#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Bouton.h"
#include "Anim.h"
#include "Legende.h"
#include <string>

struct Menu
{
	Bouton* b1;
	Bouton* b2;
	Bouton* b3;
	Bouton* b4;

	void update(float dt, sf::RenderWindow& win)
	{
		b1->update(dt, win);
		b2->update(dt, win);
		b3->update(dt, win);
		b4->update(dt, win);
	}

	void draw(sf::RenderWindow& win)
	{
		b1->draw(win);
		b2->draw(win);
		b3->draw(win);
		b4->draw(win);
	}
};

struct Text
{
	sf::Font font;
	sf::Text text;

	void init(const wchar_t * textString, int characterSize, sf::Color color, sf::Uint32 style)
	{
		font.loadFromFile("ressources/Aver.ttf");
		text.setFont(font);
		text.setFillColor(color);
		text.setString(textString);
		text.setCharacterSize(characterSize);
		text.setStyle(style);
		text.setPosition({ -500,-500 });
	}

	void draw(sf::RenderWindow & win)
	{
		win.draw(text);
	}
};

struct Page
{
	std::vector <sf::Sprite*> sprites;
	std::vector <Anim*> animations;
	std::vector <Legende*> legends;
	std::vector <Text*> textes;

	void animate()
	{
		for (unsigned int i = 0; i < animations.size(); i++)
		{
			animations[i]->start();
		}
	}

	void nextFAnim(float dt)
	{
		for (unsigned int i = 0; i < animations.size(); i++)
		{
			animations[i]->next(dt);
		}
	}

	void draw(sf::RenderWindow& win)
	{
		for (unsigned int i = 0; i < sprites.size(); i++)
		{
			win.draw(*sprites[i]);
		}
		for (unsigned int i = 0; i < legends.size(); i++)
		{
			legends[i]->draw(win);
		}
		for (unsigned int i = 0; i < textes.size(); i++)
		{
			textes[i]->draw(win);
		}
	}
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 600), "Bon Anniversaire Papa!", sf::Style::Titlebar | sf::Style::Close);

	sf::Image icone;
	icone.loadFromFile("ressources/icone.png");
	window.setIcon(256, 256, icone.getPixelsPtr());

	sf::RectangleShape bg({ 690 , 590 });
	bg.setPosition({ 305, 5 });
	bg.setOutlineThickness(5);
	bg.setFillColor(sf::Color::White);
	bg.setOutlineColor(sf::Color::Black);

	// Button on the left
	float widthB = 300;
	float heightB = 150;

	Menu myMenu;
	myMenu.b1 = new Bouton(0, 0, widthB, heightB, sf::Color(224, 80, 32), "Presentation");
	myMenu.b2 = new Bouton(0, heightB, widthB, heightB, sf::Color(224, 100, 32), "La Tireuse");
	myMenu.b3 = new Bouton(0, heightB * 2, widthB, heightB, sf::Color(224, 130, 32), "Les Futs");
	myMenu.b4 = new Bouton(0, heightB * 3, widthB, heightB, sf::Color(224, 160, 32), "Changer de Fut");

	//To do the animation only once
	bool b1Anim = true;
	bool b2Anim = true;
	bool b3Anim = true;
	bool b4Anim = true;

	// Clock init for updates
	sf::Clock gameClock;
	float dt;

	// Array
	std::vector <sf::Texture*> textures;
	std::vector <sf::Sprite*> sprites;
	std::vector <Legende*> legends;
	std::vector <Text*> textes;

	// Legends
	Legende temperature({ -500, -500 }, { -500, -500 }, Legende::Direction::Left, L"Temperature");
	Legende jauge({ -500, -500 }, { -500, -500 }, Legende::Direction::Left, L"Jauge du fut");
	Legende jours({ -500, -500 }, { -500, -500 }, Legende::Direction::Left, L"Jours restants");
	Legende verre({ -500, -500 }, { -500, -500 }, Legende::Direction::Right, L"Verre (vide bien sur)");
	Legende poignee({ -500, -500 }, { -500, -500 }, Legende::Direction::Right, L"Poignée");

	// Set Texts
	Text titreTireuse;
	titreTireuse.init(L"La Philips HD3620", 20, sf::Color::Black, sf::Text::Bold);
	textes.push_back(&titreTireuse);
	Text tuyau;
	tuyau.init(L"Chaque fût fait 6L et est fourni avec le\n tuyau qui le relie à la sortie de la tireuse\n(Pas besoin de beaucoup d'entretien)", 20, sf::Color::Black, sf::Text::Regular);
	textes.push_back(&tuyau);
	Text futs;
	futs.init(L"Types de fûts disponibles: ", 25, sf::Color::Blue, sf::Text::Regular);
	textes.push_back(&futs);
	Text listFuts;
	listFuts.init(L"\n\
		- Goose Midway\n\
		- Kwak\n\
		- Leffe (blonde/ruby/royale/brune)\n\
		- Hoegaarden\n\
		- Jupiler\n\
		- Stella Artois\n\
		- Diekirch\n\
		- Franziskaner Weissber\n\
		- Lowenbrau\n\
		- Beck's"\
		, 25, sf::Color(143, 89, 34, 210), sf::Text::Regular);
	textes.push_back(&listFuts);
	Text explain1;
	explain1.init(L"   Clipser la pompe\n(démontable) sur le fût", 17, sf::Color::Black, sf::Text::Regular);
	textes.push_back(&explain1);
	Text explain2;
	explain2.init(L"Inserer le tuyau (fourni avec le fût)\ndans la pompe (en dessous de la poignée)\net clipser la partie dure du tuyau dans la pompe\n au dessus du fût. ", 17, sf::Color::Black, sf::Text::Regular);
	textes.push_back(&explain2);
	Text explain3;
	explain3.init(L"Inserer le fût avec la pompe\n dans la tireuse en ouvrant celle-ci\n en deux, clipser le fût et\nrefermer la tireuse", 17, sf::Color::Black, sf::Text::Regular);
	textes.push_back(&explain3);
	Text explain4;
	explain4.init(L"Une démonstration par un technicien est également\nfourni avec ce logiciel", 17, sf::Color::Red, sf::Text::Regular);
	textes.push_back(&explain4);

	// Sprites and textures declaration
	sf::Texture tTireuse;
	sf::Sprite tireuse;
	sf::Texture tTireuseFace;
	sf::Sprite tireuseFace;
	sf::Texture tBonAnniv;
	sf::Sprite bonAnniv;
	sf::Texture tclips;
	sf::Sprite clips;
	sf::Texture tmise;
	sf::Sprite mise;
	sf::Texture tsemiOuverte;
	sf::Sprite semiOuverte;
	sf::Texture tmiseTuyau;
	sf::Sprite miseTuyau;
	sf::Texture tfleche;
	sf::Sprite fleche;
	sf::Sprite fleche2;

	const unsigned int nbSpriteF(6);
	const unsigned int nbLegend(5);

	// Load Textures
	for (unsigned int i = 0; i < nbSpriteF; i++)
	{
		textures.push_back(new sf::Texture);
		textures[i]->loadFromFile("ressources/" + std::to_string(i+1) + ".jpg");
		textures[i]->setSmooth(true);
	}
	tTireuse.loadFromFile("ressources/tireuse1.png");
	tTireuse.setSmooth(true);
	tTireuseFace.loadFromFile("ressources/tireuseFace.png");
	tTireuseFace.setSmooth(true);
	tBonAnniv.loadFromFile("ressources/bonanniversaire.png");
	tBonAnniv.setSmooth(true);
	tclips.loadFromFile("ressources/clips.png");
	tclips.setSmooth(true);
	tmise.loadFromFile("ressources/mise.jpg");
	tmise.setSmooth(true);
	tsemiOuverte.loadFromFile("ressources/semiOuverte.jpg");
	tsemiOuverte.setSmooth(true);
	tmiseTuyau.loadFromFile("ressources/tuyau.jpg");
	tmiseTuyau.setSmooth(true);
	tfleche.loadFromFile("ressources/fleche.jpg");
	tfleche.setSmooth(true);

	// Set sprites
	for (unsigned int i = 0; i < nbSpriteF; i++)
	{
		sprites.push_back(new sf::Sprite);
		sprites[i]->setTexture(*textures[i]);
		sprites[i]->setScale({ 0.2f,0.2f });
		if (i < 3)
			sprites[i]->setPosition(100, 180 * i + 60);
		else
			sprites[i]->setPosition(1100, 180 * (i - 3) + 60);
	}
	tireuse.setTexture(tTireuse);
	tireuse.setScale({ 0.2f, 0.2f });
	tireuse.setPosition(550, 200);

	tireuseFace.setTexture(tTireuseFace);
	tireuseFace.setScale({ 0.5f, 0.5f });
	tireuseFace.setPosition(300, 100);

	bonAnniv.setTexture(tBonAnniv);
	bonAnniv.setScale({ 0.6f , 0.6f });
	bonAnniv.setPosition(350, 50);

	clips.setTexture(tclips);
	mise.setTexture(tmise);
	semiOuverte.setTexture(tsemiOuverte);
	miseTuyau.setTexture(tmiseTuyau);
	fleche.setTexture(tfleche);
	fleche2.setTexture(tfleche);

	clips.setScale({ 0.2f , 0.2f });
	mise.setScale({ 0.17f , 0.17f });
	semiOuverte.setScale({ 0.4f , 0.4f });
	miseTuyau.setScale({ 0.35f , 0.35f });
	fleche.setScale({ 0.4f , 0.2f });
	fleche2.setScale({ 0.4f , 0.2f });

	clips.setPosition({ -500,-500 });
	mise.setPosition({ -500,-500 });
	semiOuverte.setPosition({ -500,-500 });
	miseTuyau.setPosition({ -500,-500 });
	fleche.setPosition({ -500,-500 });
	fleche2.setPosition({ -500,-500 });


	Page page1;
	page1.sprites = sprites;
	page1.sprites.push_back(&tireuse);
	page1.sprites.push_back(&bonAnniv);

	Page page2;
	page2.textes = textes;
	page2.sprites.push_back(&tireuseFace);
	page2.legends.push_back(&temperature);
	page2.legends.push_back(&jauge);
	page2.legends.push_back(&jours);
	page2.legends.push_back(&verre);
	page2.legends.push_back(&poignee);

	Page page3;
	page3.sprites.push_back(&clips);
	page3.sprites.push_back(&mise);
	page3.sprites.push_back(&semiOuverte);
	page3.sprites.push_back(&miseTuyau);
	page3.sprites.push_back(&fleche);
	page3.sprites.push_back(&fleche2);


	// Set sprites positions
	sprites[0]->setPosition(410, 140);
	sprites[1]->setPosition(350, 280);
	sprites[2]->setPosition(450, 420);
	sprites[3]->setPosition(790, 140);
	sprites[4]->setPosition(850, 280);
	sprites[5]->setPosition(750, 420);
	sprites[5]->setScale({ 0.2f,0.2f });
	tireuse.setScale({ 0.2f, 0.2f });
	tireuse.setPosition(550, 200);
	tireuseFace.setScale({ 0.5f, 0.5f });
	tireuseFace.setPosition(-500, -500);
	bonAnniv.setPosition(500, 0);
	clips.setPosition({ -500,-500 });
	mise.setPosition({ -500,-500 });
	semiOuverte.setPosition({ -500,-500 });
	miseTuyau.setPosition({ -500,-500 });
	fleche.setPosition({ -500,-500 });
	fleche2.setPosition({ -500,-500 });

	// Set legends
	temperature.setPos({ -500,-500 }, { -500,-500 });
	jauge.setPos({ -500,-500 }, { -500,-500 });
	jours.setPos({ -500,-500 }, { -500,-500 });
	verre.setPos({ -500,-500 }, { -500,-500 });
	poignee.setPos({ -500,-500 }, { -500,-500 });

	// Set Text positions
	for (unsigned int i = 0; i < textes.size(); i++)
	{
		textes[i]->text.setPosition({ -500,-500 });
	}



	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (myMenu.b1->clicked())
		{
			if (b1Anim)
			{
				// Do the B1 animation
				b1Anim = false;
				b2Anim = true;
				b3Anim = true;
				b4Anim = true;

				// Set sprites positions
				sprites[0]->setPosition(410, 140);
				sprites[1]->setPosition(350, 280);
				sprites[2]->setPosition(450, 420);
				sprites[3]->setPosition(790, 140);
				sprites[4]->setPosition(850, 280);
				sprites[5]->setPosition(750, 420);
				sprites[5]->setScale({ 0.2f,0.2f });
				tireuse.setScale({ 0.2f, 0.2f });
				tireuse.setPosition(550, 200);
				tireuseFace.setScale({ 0.5f, 0.5f });
				tireuseFace.setPosition(-500, -500);
				bonAnniv.setPosition(500, 0);
				clips.setPosition({ -500,-500 });
				mise.setPosition({ -500,-500 });
				semiOuverte.setPosition({ -500,-500 });
				miseTuyau.setPosition({ -500,-500 });
				fleche.setPosition({ -500,-500 });
				fleche2.setPosition({ -500,-500 });

				// Set legends
				temperature.setPos({ -500,-500 }, { -500,-500 });
				jauge.setPos({ -500,-500 }, { -500,-500 });
				jours.setPos({ -500,-500 }, { -500,-500 });
				verre.setPos({ -500,-500 }, { -500,-500 });
				poignee.setPos({ -500,-500 }, { -500,-500 });

				// Set Text positions
				for (unsigned int i = 0; i < textes.size(); i++)
				{
					textes[i]->text.setPosition({ -500,-500 });
				}
			}
		}
		if (myMenu.b2->clicked())
		{
			if (b2Anim)
			{
				// Do the B2 animation
				b1Anim = true;
				b2Anim = false;
				b3Anim = true;
				b4Anim = true;

				// Set sprites positions
				for (unsigned int i = 0; i < nbSpriteF; i++)
				{
					sprites[i]->setPosition(-500, -500);
				}
				tireuse.setScale({ 0.5f , 0.5f });
				tireuse.setPosition(-500, -500);
				tireuseFace.setScale({ 0.4f, 0.4f });
				tireuseFace.setPosition(480, 50);
				bonAnniv.setPosition(-500, -500);
				clips.setPosition({ -500,-500 });
				mise.setPosition({ -500,-500 });
				semiOuverte.setPosition({ -500,-500 });
				miseTuyau.setPosition({ -500,-500 });
				fleche.setPosition({ -500,-500 });
				fleche2.setPosition({ -500,-500 });

				// Set legends
				temperature.setPos({ 638, 278 }, { 450, 200 });
				jauge.setPos({ 638, 312 }, { 450, 250 });
				jours.setPos({ 638, 334 }, { 450, 310 });
				verre.setPos({ 646, 244 }, { 800, 300 });
				poignee.setPos({ 645, 88 }, { 850, 70 });

				// Set Text positions
				for (unsigned int i = 0; i < textes.size(); i++)
				{
					textes[i]->text.setPosition({ -500,-500 });
				}
				titreTireuse.text.setPosition({ 550,10 });
			}
		}
		if (myMenu.b3->clicked())
		{
			if (b3Anim)
			{
				// Do the B3 animation
				b1Anim = true;
				b2Anim = true;
				b3Anim = false;
				b4Anim = true;

				// Set sprites positions
				sprites[0]->setPosition(360, 68);
				sprites[1]->setPosition(351, 220);
				sprites[2]->setPosition(398, 376);
				sprites[3]->setPosition(861, 22);
				sprites[4]->setPosition(860, 204);
				sprites[5]->setPosition(800, 360);
				sprites[5]->setScale({ 0.2f,0.2f });
				tireuse.setPosition(-500, -500);
				tireuseFace.setPosition(-500, -500);
				bonAnniv.setPosition(-500, -500);
				clips.setPosition({ -500,-500 });
				mise.setPosition({ -500,-500 });
				semiOuverte.setPosition({ -500,-500 });
				miseTuyau.setPosition({ -500,-500 });
				fleche.setPosition({ -500,-500 });
				fleche2.setPosition({ -500,-500 });

				// Set legends
				temperature.setPos({ -500,-500 }, { -500,-500 });
				jauge.setPos({ -500,-500 }, { -500,-500 });
				jours.setPos({ -500,-500 }, { -500,-500 });
				verre.setPos({ -500,-500 }, { -500,-500 });
				poignee.setPos({ -500,-500 }, { -500,-500 });

				// Set Text positions
				for (unsigned int i = 0; i < textes.size(); i++)
				{
					textes[i]->text.setPosition({ -500,-500 });
				}
				tuyau.text.setPosition({ 475,510 });
				listFuts.text.setPosition({ 350 + (700 - listFuts.text.getGlobalBounds().width)/2, (600 - listFuts.text.getGlobalBounds().height)/2 - 100 });
				futs.text.setPosition({ 330,20 });
			}
		}
		if (myMenu.b4->clicked())
		{
			if (b4Anim)
			{
				// Do the B4 animation
				b1Anim = true;
				b2Anim = true;
				b3Anim = true;
				b4Anim = false;

				// Set sprites positions
				for (unsigned int i = 0; i < nbSpriteF; i++)
				{
					sprites[i]->setPosition(-500, -500);
				}
				tireuse.setPosition(-500, -500);
				tireuseFace.setPosition(-500, -500);
				bonAnniv.setPosition(-500, -500);

				sprites[5]->setScale({ 0.3f,0.3f });

				clips.setPosition({ 340,20 });
				fleche.setPosition({ 630,74 });
				sprites[5]->setPosition({ 780,10 });

				miseTuyau.setPosition({ 370,200 });

				mise.setPosition({ 370,400 });
				semiOuverte.setPosition({ 780,370 });
				fleche2.setPosition({ 590,400 });

				// Set legends
				temperature.setPos({ -500,-500 }, { -500,-500 });
				jauge.setPos({ -500,-500 }, { -500,-500 });
				jours.setPos({ -500,-500 }, { -500,-500 });
				verre.setPos({ -500,-500 }, { -500,-500 });
				poignee.setPos({ -500,-500 }, { -500,-500 });

				// Set Text positions
				for (unsigned int i = 0; i < textes.size(); i++)
				{
					textes[i]->text.setPosition({ -500,-500 });
				}
				explain1.text.setPosition({ 600,136 });
				explain2.text.setPosition({ 590,235 });
				explain3.text.setPosition({ 562,480 });
				explain4.text.setPosition({ 324,10 });
			}
		}

		dt = gameClock.restart().asSeconds();

		// Updates
		myMenu.update(dt, window);

		// Clear
		window.clear();

		// Draw
		window.draw(bg);
		page1.draw(window);
		page2.draw(window);
		page3.draw(window);
		myMenu.draw(window);

		window.display();
	}

	return 0;
}