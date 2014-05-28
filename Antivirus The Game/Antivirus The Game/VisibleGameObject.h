#pragma once

class VisibleGameObject
{
public:
	VisibleGameObject();
	virtual ~VisibleGameObject();

	virtual void load(string filename);
	virtual void draw(sf::RenderWindow &window);
	virtual void update(float elapsedTime);
	
	sf::Sprite& getSprite(); 

	virtual void setPosition(float x, float y);
	virtual sf::Vector2f getPosition() const;
	virtual bool isLoaded() const;
	virtual void setExisted(bool);
	virtual bool isExisted() const;
	virtual string getType();
	virtual void setType(string);

protected:
private:
	sf::Sprite _sprite;
	sf::Texture _texture;
	string _filename;
	bool _isLoaded;
	bool _isExisted;
	string _type;
};