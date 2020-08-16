#include "interface.h"

interface::interface() {
	this->view = 1;

	this->window = new sf::RenderWindow(sf::VideoMode(1700, 900), "Astronaute", sf::Style::Close);
	this->background = new sf::RectangleShape(sf::Vector2f(1700, 900));
	this->spriteBackground = new sf::Texture;
	this->spriteBackground->loadFromFile("sprites/backgrounds/univers.png");
	this->background->setTexture(this->spriteBackground);
	this->background->setPosition(0, 0);

	this->mouseHitbox = new sf::CircleShape(10);
	this->mouseHitbox->setPosition(this->mousePos.x, this->mousePos.y);
	sf::FloatRect mouseHitboxRect = this->mouseHitbox->getLocalBounds();
	this->mouseHitbox->setOrigin(mouseHitboxRect.left + mouseHitboxRect.width / 2.0f,
		mouseHitboxRect.top + mouseHitboxRect.height / 2.0f);
	this->mouseHitbox->setFillColor(sf::Color::Green);
}

void interface::detectionEvents() {
	sf::Event evnt;
	while (this->window->pollEvent(evnt))
	{
		switch (evnt.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		}
	}

}

void interface::drawBackground() {
	this->window->draw(*this->background);
	//this->window->draw(*this->mouseHitbox);
}

void interface::affichageView(univers* TheUniverse) {
	if (this->view == 0) {
		//je mettrais l'ecran titre ici
	}

	else if (this->view >= 1 && this->view <=4) {
		TheUniverse->afficher(this->window, this->mousePos, this->view);
	}

	else if (this->view == 5) {
		this->galaxieView->afficherSystemes(this->window);
	}

	else if (this->view == 6) {
		this->systemeView->afficherPlanetes(this->window);
	}

	else if (this->view == 7) {
		this->planeteView->afficherCouches(this->window);
	}
}

void interface::detectionClic(univers* TheUniverse) {
	bool isClic = 0;

	if (this->view >= 1 && this->view <= 4) {
		for (int i = 0; i < TheUniverse->getGalaxies(this->view).size(); i++) {
			if (this->mousePos.x <= TheUniverse->getGalaxies(this->view)[i]->getPosition().x + 125
				&& mousePos.x >= TheUniverse->getGalaxies(this->view)[i]->getPosition().x - 125
				&& mousePos.y <= TheUniverse->getGalaxies(this->view)[i]->getPosition().y + 125
				&& mousePos.y >= TheUniverse->getGalaxies(this->view)[i]->getPosition().y - 125) {

				cout << TheUniverse->getGalaxies(this->view)[i]->getType() << endl;
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
					this->galaxieView = TheUniverse->getGalaxies(this->view)[i];
					isClic = 1;
				}
				while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) { }
			}
		}
	}

	if (this->view == 5) {
		for (int i = 0; i < this->galaxieView->getSystemes().size(); i++) {
			if (this->mousePos.x <= this->galaxieView->getSystemes()[i]->getPosition().x + 70
				&& mousePos.x >= this->galaxieView->getSystemes()[i]->getPosition().x - 70
				&& mousePos.y <= this->galaxieView->getSystemes()[i]->getPosition().y + 70
				&& mousePos.y >= this->galaxieView->getSystemes()[i]->getPosition().y - 70) {

				cout << "Il y a " << this->galaxieView->getSystemes()[i]->getNombre() << " planetes dans ce systeme" << endl;
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
					this->systemeView = this->galaxieView->getSystemes()[i];
					isClic = 1;
				}
				while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) { }
			}
		}
	}

	if (this->view == 6) {
		for (int i = 0; i < this->systemeView->getNombre(); i++) {
			if (this->mousePos.x <= this->systemeView->getPlanetes()[i]->getPosition().x + 70
				&& mousePos.x >= this->systemeView->getPlanetes()[i]->getPosition().x - 70
				&& mousePos.y <= this->systemeView->getPlanetes()[i]->getPosition().y + 70
				&& mousePos.y >= this->systemeView->getPlanetes()[i]->getPosition().y - 70) {

				cout << "Cette planete est de type " << this->systemeView->getPlanetes()[i]->getType() << " et de sous-type " << this->systemeView->getPlanetes()[i]->getSousType() << endl;
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
					this->planeteView = this->systemeView->getPlanetes()[i];
					isClic = 1;
				}
				while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {}
			}
		}
	}


	if (isClic == 1 && (this->view >= 1 && this->view <= 4)) {
		this->view = 5;
		isClic = 0;
	}

	if (isClic == 1 && this->view == 5) {
		this->view = 6;
		isClic = 0;
	}

	if (isClic == 1 && this->view == 6) {
		this->view = 7;
		isClic = 0;
	}

}