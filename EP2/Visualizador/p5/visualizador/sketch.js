//Constantes
let PERSON_RADIUS = 40;

let HOMEM = 0
let MULHER = 1

let HORIZONTAL = 0
let VERTIAL = 1

let UNLOCKED = 0
let LOCKED = 1


let SAIU_DO_BANHEIRO = 0
let ENTROU_NO_BANHEIRO = 1
let CHEGOU_NO_ESTABELECIMENTO = 5
let ENTROU_NA_FILA = 2

let BLOQUEOU_SEMAFORO = 3
let LIBEROU_SEMAFORO = 4

let SEME = 6
let SEMH = 7
let SEMM = 8

let bathroom
let state = [-1,-1]
let lastState = [-2,-2]

//O log
let strings
let changed = 0
let currentLine = 0
////////////////////////////////////////////////////////////////
function Semaphore(x,y,r){
	this.pos = [x,y]
	this.state = UNLOCKED
	this.lock = function () {
		this.state = LOCKED
	}
	this.unlock = function() {
		this.state= UNLOCKED
	}

	this.draw = function(){
		noStroke()
		if(this.state == LOCKED)
			fill(241, 18, 0, 200)
		else
			fill(0, 190, 12, 200)

		ellipseMode(CENTER)
		ellipse(this.pos[0], this.pos[1], r)
	}
}
////////////////////////////////////////////////////////////////
function Bathroom(x,y,w,h,slots,q){
	this.pos = [x,y]
	this.w = w
	this.h = h
	this.slots = new Queue(x,y,x,y+h,slots)
	this.mLine = new Queue(x+w + 40, y + h/4 , 4*(x+w+windowWidth)/7 + 40 , y+h/2,q)
	this.fLine = new Queue(x+w + 40, y + 3*h/4 , 4*(x+w+windowWidth)/7 + 40 , y+h/2,q)

	this.waitingLine = new Queue(x-60,y,x-60,y+h,slots)
	this.semHomem = new Semaphore(x+w + 20, y + h/4, 39)
	this.semMulher = new Semaphore(x+w + 20, y + 3*h/4, 39)
	this.semE = new Semaphore(x+w + 20, y + h/2, 39)

	this.semHomem.lock()
	this.semMulher.lock()
	

	this.draw = function(){
		noStroke()
		this.mLine.draw()
		this.fLine.draw()
		this.slots.draw()
		this.semHomem.draw()
		this.semMulher.draw()
		this.semE.draw()
		this.waitingLine.draw()
		fill(255,255,255, 30)
		rect(this.pos[0], this.pos[1] - PERSON_RADIUS/2, this.w, this.h, 10)
	}

	this.update = function(){
		if(changed == 0) return

		changed = 0

		newState = JSON.parse(strings[currentLine])
		state[0] = newState.signal
		state[1] = newState.id

		signal = state[0]
		id = state[1]

		console.log(state.toString())

		switch(signal){
		case CHEGOU_NO_ESTABELECIMENTO:
			bathroom.waitingLine.add({id:id, gender:(id%2 != 0)? HOMEM:MULHER})
			break
		case ENTROU_NA_FILA:
			if( state[1] %2 != 0){
				if(bathroom.waitingLine.people.find((each)=>{
					if(each.id == state[1]) 
						return true
				}) != undefined){
					bathroom.waitingLine.remove(state[1])
					bathroom.mLine.add({id:state[1], gender:HOMEM})
				}
			}
			else
				if(bathroom.waitingLine.people.find((each)=>{
					if(each.id == state[1]) 
						return true
				}) != undefined){
					bathroom.waitingLine.remove(state[1])
					bathroom.fLine.add({id:state[1], gender:MULHER})
				}

			break;
		case ENTROU_NO_BANHEIRO:
			if( state[1] %2 != 0){//Se for homem
				if(this.waitingLine.people.find((each)=>{if(each.id == id) return true}) != undefined){
					//Se veio da waiting line
					this.waitingLine.remove(id)
					this.slots.add({id:id, gender:HOMEM})
				}
				else{
					//Se veio da fila
					this.mLine.remove(id)
					this.slots.add({id:id, gender:HOMEM})
				}
			}
			else{
				if(this.waitingLine.people.find((each)=>{if(each.id == id) return true}) != undefined){
					//Se veio da waiting line
					this.waitingLine.remove(id)
					this.slots.add({id:id, gender:MULHER})
				}
				else{
					//Se veio da fila
					this.fLine.remove(id)
					this.slots.add({id:id, gender:MULHER})
				}	
			}
			break
		case SAIU_DO_BANHEIRO:
			bathroom.slots.remove(id)
			bathroom.waitingLine.add({id:id, gender:(id % 2 != 0)? HOMEM:MULHER})
			break
		case LIBEROU_SEMAFORO:
			if(id == SEME)
				this.semE.unlock()
			else if(id == SEMH)
				this.semHomem.unlock()
			else if(id == SEMM)
				this.semMulher.unlock()
			break
		case BLOQUEOU_SEMAFORO:
			if(id == SEME)
				this.semE.lock()
			else if(id == SEMH)
				this.semHomem.lock()
			else if(id == SEMM)
				this.semMulher.lock()
			break
		default:
			break
		}
	}
}
////////////////////////////////////////////////////////////////
function Queue(x0,y0, x,y,q){
	if(q<=0){
		alert("Invalid q")
	}
	this.start = [x0,y0]
	this.end = [x,y]
	this.length = q
	this.people = []
	this.current = 0

	for(var i = 0; i < q; i++){
		this.people.push(new Pessoa(0, 0)) 
	}

	this.add = function(value){
		if(this.current == this.length){
			alert("Fila esta cheia! Nao pode adicionar mais pessoas")
		}
		else if(value == undefined){
			alert("Pessoa undefined")
		}
		else{
		this.people[this.current].id = value.id
		this.people[this.current].gender = value.gender
		this.current = this.current + 1
		}
		
	}

	this.remove = function(id){
		if(id == undefined){
			var ret = this.people[0]

			for(var i = 0; i < this.current-1; i++){
				this.people[i].id = this.people[i+1].id
				this.people[i].gender = this.people[i+1].gender
			}

			this.current--
			this.people[this.current].id = 0;
			this.people[this.current].gender = 0;
		
			return ret
		}
		else{
			index = this.people.findIndex((each)=>{
				if(each.id == id)
					return true
			})
			if(index != -1){
				for(var i = index; i < this.current-1; i++){
					this.people[i].id = this.people[i+1].id
					this.people[i].gender = this.people[i+1].gender
				}
				this.current--
				this.people[this.current].id = 0
				this.people[this.current].gender = 0

				return this.people[index]
			} 
			else{
				return -1
			}
		}
	}

		
	this.draw = function (){
			fill(101,111,111,100)

			if(this.end[0] - this.start[0] > this.end[1] - this.start[1])
				rect(this.start[0], this.start[1] - PERSON_RADIUS/2, this.end[0] - this.start[0] + PERSON_RADIUS/3, 40, 10)			
			else
				rect(this.start[0], this.start[1] - PERSON_RADIUS/2,40, this.end[1] - this.start[1], 10)			


			for(var i = 0; i < q; i++){
				if(this.people[i].id > 0){
						var thisPosition
						if(this.end[0] - this.start[0] > this.end[1] - this.start[1])
							thisPosition = [(this.end[0] - this.start[0])/this.current*i + this.start[0], this.start[1]]
						else
							thisPosition = [(this.end[0] - this.start[0])/this.current*i + this.start[0], (this.end[1]-this.start[0])/this.current*i + this.start[1]]

						if(this.people[i].gender == MULHER)
							fill(255,51,153, 200)
						else
							fill(14,119,220, 200)

						noStroke()
						ellipse(thisPosition[0] + PERSON_RADIUS/2, thisPosition[1], PERSON_RADIUS)
						textAlign(CENTER)
						ellipseMode(CENTER)
						fill(255,255,255,255)
						text(this.people[i].id, thisPosition[0] + PERSON_RADIUS/2, thisPosition[1]+3)
					}
					
				}
			}
}	
////////////////////////////////////////////////////////////////
function Pessoa(gender,id){
		this.id = id
	this.gender = gender
}
var id = 1;
////////////////////////////////////////////////////////////////
function keyPressed(){
	if(keyCode == ENTER){
		currentLine++
		changed = 1
	}
}
////////////////////////////////////////////////////////////////
var signalEntrouBanheiro
var signalSaiuBanheiro
var signalEntrouFila
var signalEntrouEstabelecimento
var signalBloqueouSem
var signalLiberouSem
var input

var buttonPosX = 40
var offset = 0

function setup() {
	bathroom = new Bathroom(100,100, 120,windowHeight - 200, 100, 10)
	createCanvas(windowWidth, windowHeight);
	
	input = createInput()
	input.position(windowHeight/2, 100)


	signalEntrouBanheiro = createButton('Entrou Banheiro')
	signalEntrouBanheiro.position(40 + offset, windowHeight - 40)
	offset += windowWidth/6

	signalEntrouBanheiro.mousePressed(function () {
		state[0] = ENTROU_NO_BANHEIRO
		state[1] = input.value()
		changed = 1
	})

	signalEntrouFila = createButton('Entrou fila')
	signalEntrouFila.position(40 + offset, windowHeight - 40)
	signalEntrouFila.mousePressed(function(){
		state[0] = ENTROU_NA_FILA
		state[1] = input.value()
		changed = 1
	})
	offset += windowWidth/6

	signalEntrouEstabelecimento = createButton('Entrou mall')
	signalEntrouEstabelecimento.position(40 + offset, windowHeight - 40)
	signalEntrouEstabelecimento.mousePressed(function (){
		state[0] = CHEGOU_NO_ESTABELECIMENTO
		state[1] = input.value()
		changed = 1
	})
	offset += windowWidth/6

	signalSaiuBanheiro = createButton('Saiu banheiro')
	signalSaiuBanheiro.position(40+offset, windowHeight - 40)
	signalSaiuBanheiro.mousePressed(function(){
		state[0] = SAIU_DO_BANHEIRO
		state[1] = input.value()
		changed = 1
	})
	offset += windowWidth/6

	signalBloqueouSem = createButton('Bloqueou sem')
	signalBloqueouSem.position(40+offset, windowHeight - 40)
	signalBloqueouSem.mousePressed(function(){
		state[0] = BLOQUEOU_SEMAFORO 
		state[1] = input.value()
		changed = 1
	})
	offset += windowWidth/6

	signalLiberouSem = createButton('Liberal sem')
	signalLiberouSem.position(40+offset, windowHeight - 40)
	signalLiberouSem.mousePressed(function(){
		state[0] = LIBEROU_SEMAFORO
		state[1] = input.value()
		changed = 1
	})
	offset += windowWidth/6

	input.value('')

}

function preload(){
	strings = loadStrings('log.txt')
}

function draw() {
	background(40,40,40)
	bathroom.update()
	bathroom.draw()
}
